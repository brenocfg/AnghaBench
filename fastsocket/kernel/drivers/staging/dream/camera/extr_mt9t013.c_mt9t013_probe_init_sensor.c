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
struct msm_camera_sensor_info {int /*<<< orphan*/  sensor_reset; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*,scalar_t__) ; 
 int ENODEV ; 
 scalar_t__ MT9T013_MODEL_ID ; 
 int /*<<< orphan*/  MT9T013_REG_MODEL_ID ; 
 int MT9T013_REG_RESET_REGISTER ; 
 int MT9T013_RESET_DELAY_MSECS ; 
 int MT9T013_RESET_REGISTER_PWON ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 TYPE_1__* mt9t013_client ; 
 int mt9t013_i2c_read_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int mt9t013_i2c_write_w (int /*<<< orphan*/ ,int,int) ; 
 int mt9t013_set_default_focus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt9t013_probe_init_sensor(const struct msm_camera_sensor_info *data)
{
	int rc;
	uint16_t chipid;

	rc = gpio_request(data->sensor_reset, "mt9t013");
	if (!rc)
		gpio_direction_output(data->sensor_reset, 1);
	else
		goto init_probe_done;

	mdelay(20);

	/* RESET the sensor image part via I2C command */
	rc = mt9t013_i2c_write_w(mt9t013_client->addr,
		MT9T013_REG_RESET_REGISTER, 0x1009);
	if (rc < 0)
		goto init_probe_fail;

	/* 3. Read sensor Model ID: */
	rc = mt9t013_i2c_read_w(mt9t013_client->addr,
		MT9T013_REG_MODEL_ID, &chipid);

	if (rc < 0)
		goto init_probe_fail;

	CDBG("mt9t013 model_id = 0x%x\n", chipid);

	/* 4. Compare sensor ID to MT9T012VC ID: */
	if (chipid != MT9T013_MODEL_ID) {
		rc = -ENODEV;
		goto init_probe_fail;
	}

	rc = mt9t013_i2c_write_w(mt9t013_client->addr,
		0x3064, 0x0805);
	if (rc < 0)
		goto init_probe_fail;

	mdelay(MT9T013_RESET_DELAY_MSECS);

	goto init_probe_done;

	/* sensor: output enable */
#if 0
	rc = mt9t013_i2c_write_w(mt9t013_client->addr,
		MT9T013_REG_RESET_REGISTER,
		MT9T013_RESET_REGISTER_PWON);

	/* if this fails, the sensor is not the MT9T013 */
	rc = mt9t013_set_default_focus(0);
#endif

init_probe_fail:
	gpio_direction_output(data->sensor_reset, 0);
	gpio_free(data->sensor_reset);
init_probe_done:
	return rc;
}