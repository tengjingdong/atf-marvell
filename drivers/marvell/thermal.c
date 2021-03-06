/*
 * Copyright (C) 2017 Marvell International Ltd.
 *
 * SPDX-License-Identifier:	GPL-2.0
 * https://spdx.org/licenses
 */

#include <debug.h>
#include <thermal.h>

int marvell_thermal_init(struct tsen_config *tsen_cfg)
{
	if (tsen_cfg->tsen_ready == 1) {
		INFO("thermal sensor is already initialized\n");
		return 0;
	}

	if (tsen_cfg->ptr_tsen_probe == NULL) {
		ERROR("initial thermal sensor configuration is missing\n");
		return -1;
	}

	if (tsen_cfg->ptr_tsen_probe(tsen_cfg)) {
		ERROR("thermal sensor initialization failed\n");
		return -1;
	}

	INFO("thermal sensor was initialized\n");

	return 0;
}

int marvell_thermal_read(struct tsen_config *tsen_cfg, int *temp)
{
	if (temp == NULL) {
		ERROR("NULL pointer for temperature read\n");
		return -1;
	}

	if (tsen_cfg->ptr_tsen_read == NULL ||
	    tsen_cfg->tsen_ready == 0) {
		ERROR("thermal sensor was not initialized\n");
		return -1;
	}

	if (tsen_cfg->ptr_tsen_read(tsen_cfg, temp)) {
		ERROR("temperature read failed\n");
		return -1;
	}

	return 0;
}
