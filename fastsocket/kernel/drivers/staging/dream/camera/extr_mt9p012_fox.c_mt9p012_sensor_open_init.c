#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mt9p012_ctrl {int dummy; } ;
struct msm_camera_sensor_info {int /*<<< orphan*/  vcm_pwd; } ;
typedef  int int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int fps_divider; int pict_fps_divider; scalar_t__ prev_res; struct msm_camera_sensor_info const* sensordata; int /*<<< orphan*/  pict_res; int /*<<< orphan*/  set_test; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FULL_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MT9P012_DEFAULT_CLOCK_RATE ; 
 int /*<<< orphan*/  MT9P012_REG_RESET_REGISTER ; 
 int /*<<< orphan*/  MT9P012_RESET_REGISTER_PWON ; 
 scalar_t__ QTR_SIZE ; 
 int /*<<< orphan*/  REG_INIT ; 
 int /*<<< orphan*/  RES_CAPTURE ; 
 int /*<<< orphan*/  RES_PREVIEW ; 
 int /*<<< orphan*/  TEST_OFF ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msm_camio_camif_pad_reg_reset () ; 
 int /*<<< orphan*/  msm_camio_clk_rate_set (int /*<<< orphan*/ ) ; 
 TYPE_2__* mt9p012_client ; 
 TYPE_1__* mt9p012_ctrl ; 
 int mt9p012_i2c_write_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9p012_probe_init_done (struct msm_camera_sensor_info const*) ; 
 int mt9p012_probe_init_sensor (struct msm_camera_sensor_info const*) ; 
 int mt9p012_set_default_focus () ; 
 int mt9p012_setting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt9p012_sensor_open_init(const struct msm_camera_sensor_info *data)
{
	int32_t  rc;

	mt9p012_ctrl = kzalloc(sizeof(struct mt9p012_ctrl), GFP_KERNEL);
	if (!mt9p012_ctrl) {
		CDBG("mt9p012_init failed!\n");
		rc = -ENOMEM;
		goto init_done;
	}

	mt9p012_ctrl->fps_divider = 1 * 0x00000400;
	mt9p012_ctrl->pict_fps_divider = 1 * 0x00000400;
	mt9p012_ctrl->set_test = TEST_OFF;
	mt9p012_ctrl->prev_res = QTR_SIZE;
	mt9p012_ctrl->pict_res = FULL_SIZE;

	if (data)
		mt9p012_ctrl->sensordata = data;

	/* enable mclk first */
	msm_camio_clk_rate_set(MT9P012_DEFAULT_CLOCK_RATE);
	mdelay(20);

	msm_camio_camif_pad_reg_reset();
	mdelay(20);

	rc = mt9p012_probe_init_sensor(data);
	if (rc < 0)
		goto init_fail1;

	if (mt9p012_ctrl->prev_res == QTR_SIZE)
		rc = mt9p012_setting(REG_INIT, RES_PREVIEW);
	else
		rc = mt9p012_setting(REG_INIT, RES_CAPTURE);

	if (rc < 0) {
		CDBG("mt9p012_setting failed. rc = %d\n", rc);
		goto init_fail1;
	}

	/* sensor : output enable */
	CDBG("mt9p012_sensor_open_init(): enabling output.\n");
	rc = mt9p012_i2c_write_w(mt9p012_client->addr,
		MT9P012_REG_RESET_REGISTER, MT9P012_RESET_REGISTER_PWON);
	if (rc < 0) {
		CDBG("sensor output enable failed. rc = %d\n", rc);
		goto init_fail1;
	}

	/* TODO: enable AF actuator */
#if 0
	CDBG("enable AF actuator, gpio = %d\n",
		mt9p012_ctrl->sensordata->vcm_pwd);
	rc = gpio_request(mt9p012_ctrl->sensordata->vcm_pwd, "mt9p012");
	if (!rc)
		gpio_direction_output(mt9p012_ctrl->sensordata->vcm_pwd, 1);
	else {
		CDBG("mt9p012_ctrl gpio request failed!\n");
		goto init_fail1;
	}
	mdelay(20);

	rc = mt9p012_set_default_focus();
#endif
	if (rc >= 0)
		goto init_done;

	/* TODO:
	 * gpio_direction_output(mt9p012_ctrl->sensordata->vcm_pwd, 0);
	 * gpio_free(mt9p012_ctrl->sensordata->vcm_pwd); */
init_fail1:
	mt9p012_probe_init_done(data);
	kfree(mt9p012_ctrl);
init_done:
	return rc;
}