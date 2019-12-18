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
struct s5k3e2fx_ctrl {int dummy; } ;
struct msm_camera_sensor_info {int dummy; } ;
typedef  int int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int fps_divider; int pict_fps_divider; scalar_t__ prev_res; struct msm_camera_sensor_info const* sensordata; int /*<<< orphan*/  pict_res; int /*<<< orphan*/  set_test; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  S_FULL_SIZE ; 
 scalar_t__ S_QTR_SIZE ; 
 int /*<<< orphan*/  S_REG_INIT ; 
 int /*<<< orphan*/  S_RES_CAPTURE ; 
 int /*<<< orphan*/  S_RES_PREVIEW ; 
 int /*<<< orphan*/  S_TEST_OFF ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msm_camio_camif_pad_reg_reset () ; 
 int /*<<< orphan*/  msm_camio_clk_rate_set (int) ; 
 TYPE_2__* s5k3e2fx_client ; 
 TYPE_1__* s5k3e2fx_ctrl ; 
 int s5k3e2fx_i2c_write_b (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  s5k3e2fx_probe_init_done (struct msm_camera_sensor_info const*) ; 
 int s5k3e2fx_probe_init_sensor (struct msm_camera_sensor_info const*) ; 
 int s5k3e2fx_setting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5k3e2fx_sensor_open_init(const struct msm_camera_sensor_info *data)
{
	int32_t  rc;

	s5k3e2fx_ctrl = kzalloc(sizeof(struct s5k3e2fx_ctrl), GFP_KERNEL);
	if (!s5k3e2fx_ctrl) {
		CDBG("s5k3e2fx_init failed!\n");
		rc = -ENOMEM;
		goto init_done;
	}

	s5k3e2fx_ctrl->fps_divider = 1 * 0x00000400;
	s5k3e2fx_ctrl->pict_fps_divider = 1 * 0x00000400;
	s5k3e2fx_ctrl->set_test = S_TEST_OFF;
	s5k3e2fx_ctrl->prev_res = S_QTR_SIZE;
	s5k3e2fx_ctrl->pict_res = S_FULL_SIZE;

	if (data)
		s5k3e2fx_ctrl->sensordata = data;

	/* enable mclk first */
	msm_camio_clk_rate_set(24000000);
	mdelay(20);

	msm_camio_camif_pad_reg_reset();
	mdelay(20);

	rc = s5k3e2fx_probe_init_sensor(data);
	if (rc < 0)
		goto init_fail1;

	if (s5k3e2fx_ctrl->prev_res == S_QTR_SIZE)
		rc = s5k3e2fx_setting(S_REG_INIT, S_RES_PREVIEW);
	else
		rc = s5k3e2fx_setting(S_REG_INIT, S_RES_CAPTURE);

	if (rc < 0) {
		CDBG("s5k3e2fx_setting failed. rc = %d\n", rc);
		goto init_fail1;
	}

	/* initialize AF */
	if ((rc = s5k3e2fx_i2c_write_b(s5k3e2fx_client->addr,
			0x3146, 0x3A)) < 0)
		goto init_fail1;

	if ((rc = s5k3e2fx_i2c_write_b(s5k3e2fx_client->addr,
			0x3130, 0x03)) < 0)
		goto init_fail1;

	goto init_done;

init_fail1:
	s5k3e2fx_probe_init_done(data);
	kfree(s5k3e2fx_ctrl);
init_done:
	return rc;
}