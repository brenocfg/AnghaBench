#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct msm_camera_sensor_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*,...) ; 
 int EINVAL ; 
 scalar_t__ MT9D112_MODEL_ID ; 
 int REG_MT9D112_MCU_BOOT ; 
 int /*<<< orphan*/  REG_MT9D112_MODEL_ID ; 
 int REG_MT9D112_SENSOR_RESET ; 
 int REG_MT9D112_STANDBY_CONTROL ; 
 int /*<<< orphan*/  WORD_LEN ; 
 int /*<<< orphan*/  mdelay (int) ; 
 TYPE_1__* mt9d112_client ; 
 int mt9d112_i2c_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int mt9d112_i2c_write (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int mt9d112_reg_init () ; 
 int mt9d112_reset (struct msm_camera_sensor_info const*) ; 

__attribute__((used)) static int mt9d112_sensor_init_probe(const struct msm_camera_sensor_info *data)
{
	uint16_t model_id = 0;
	int rc = 0;

	CDBG("init entry \n");
	rc = mt9d112_reset(data);
	if (rc < 0) {
		CDBG("reset failed!\n");
		goto init_probe_fail;
	}

	mdelay(5);

	/* Micron suggested Power up block Start:
	* Put MCU into Reset - Stop MCU */
	rc = mt9d112_i2c_write(mt9d112_client->addr,
		REG_MT9D112_MCU_BOOT, 0x0501, WORD_LEN);
	if (rc < 0)
		goto init_probe_fail;

	/* Pull MCU from Reset - Start MCU */
	rc = mt9d112_i2c_write(mt9d112_client->addr,
		REG_MT9D112_MCU_BOOT, 0x0500, WORD_LEN);
	if (rc < 0)
		goto init_probe_fail;

	mdelay(5);

	/* Micron Suggested - Power up block */
	rc = mt9d112_i2c_write(mt9d112_client->addr,
		REG_MT9D112_SENSOR_RESET, 0x0ACC, WORD_LEN);
	if (rc < 0)
		goto init_probe_fail;

	rc = mt9d112_i2c_write(mt9d112_client->addr,
		REG_MT9D112_STANDBY_CONTROL, 0x0008, WORD_LEN);
	if (rc < 0)
		goto init_probe_fail;

	/* FUSED_DEFECT_CORRECTION */
	rc = mt9d112_i2c_write(mt9d112_client->addr,
		0x33F4, 0x031D, WORD_LEN);
	if (rc < 0)
		goto init_probe_fail;

	mdelay(5);

	/* Micron suggested Power up block End */
	/* Read the Model ID of the sensor */
	rc = mt9d112_i2c_read(mt9d112_client->addr,
		REG_MT9D112_MODEL_ID, &model_id, WORD_LEN);
	if (rc < 0)
		goto init_probe_fail;

	CDBG("mt9d112 model_id = 0x%x\n", model_id);

	/* Check if it matches it with the value in Datasheet */
	if (model_id != MT9D112_MODEL_ID) {
		rc = -EINVAL;
		goto init_probe_fail;
	}

	rc = mt9d112_reg_init();
	if (rc < 0)
		goto init_probe_fail;

	return rc;

init_probe_fail:
	return rc;
}