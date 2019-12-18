#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mt9t013_ctrl {int dummy; } ;
struct msm_camera_sensor_info {int dummy; } ;
typedef  int int32_t ;
struct TYPE_4__ {int fps_divider; int pict_fps_divider; scalar_t__ prev_res; struct msm_camera_sensor_info const* sensordata; int /*<<< orphan*/  pict_res; int /*<<< orphan*/  set_test; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FULL_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MT9T013_DEFAULT_CLOCK_RATE ; 
 scalar_t__ QTR_SIZE ; 
 int /*<<< orphan*/  REG_INIT ; 
 int /*<<< orphan*/  RES_CAPTURE ; 
 int /*<<< orphan*/  RES_PREVIEW ; 
 int /*<<< orphan*/  TEST_OFF ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msm_camio_camif_pad_reg_reset () ; 
 int /*<<< orphan*/  msm_camio_clk_rate_set (int /*<<< orphan*/ ) ; 
 TYPE_1__* mt9t013_ctrl ; 
 int mt9t013_poweron_af () ; 
 int mt9t013_probe_init_sensor (struct msm_camera_sensor_info const*) ; 
 int mt9t013_setting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int mt9t013_sensor_open_init(const struct msm_camera_sensor_info *data)
{
	int32_t  rc;

	mt9t013_ctrl = kzalloc(sizeof(struct mt9t013_ctrl), GFP_KERNEL);
	if (!mt9t013_ctrl) {
		pr_err("mt9t013_init failed!\n");
		rc = -ENOMEM;
		goto init_done;
	}

	mt9t013_ctrl->fps_divider = 1 * 0x00000400;
	mt9t013_ctrl->pict_fps_divider = 1 * 0x00000400;
	mt9t013_ctrl->set_test = TEST_OFF;
	mt9t013_ctrl->prev_res = QTR_SIZE;
	mt9t013_ctrl->pict_res = FULL_SIZE;

	if (data)
		mt9t013_ctrl->sensordata = data;

	/* enable mclk first */
	msm_camio_clk_rate_set(MT9T013_DEFAULT_CLOCK_RATE);
	mdelay(20);

	msm_camio_camif_pad_reg_reset();
	mdelay(20);

	rc = mt9t013_probe_init_sensor(data);
	if (rc < 0)
		goto init_fail;

	if (mt9t013_ctrl->prev_res == QTR_SIZE)
		rc = mt9t013_setting(REG_INIT, RES_PREVIEW);
	else
		rc = mt9t013_setting(REG_INIT, RES_CAPTURE);

	if (rc >= 0)
		rc = mt9t013_poweron_af();

	if (rc < 0)
		goto init_fail;
	else
		goto init_done;

init_fail:
	kfree(mt9t013_ctrl);
init_done:
	return rc;
}