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
struct mt9d112_ctrl {int dummy; } ;
struct msm_camera_sensor_info {int dummy; } ;
struct TYPE_4__ {struct msm_camera_sensor_info const* sensordata; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msm_camio_camif_pad_reg_reset () ; 
 int /*<<< orphan*/  msm_camio_clk_rate_set (int) ; 
 TYPE_1__* mt9d112_ctrl ; 
 int mt9d112_sensor_init_probe (struct msm_camera_sensor_info const*) ; 

int mt9d112_sensor_init(const struct msm_camera_sensor_info *data)
{
	int rc = 0;

	mt9d112_ctrl = kzalloc(sizeof(struct mt9d112_ctrl), GFP_KERNEL);
	if (!mt9d112_ctrl) {
		CDBG("mt9d112_init failed!\n");
		rc = -ENOMEM;
		goto init_done;
	}

	if (data)
		mt9d112_ctrl->sensordata = data;

	/* Input MCLK = 24MHz */
	msm_camio_clk_rate_set(24000000);
	mdelay(5);

	msm_camio_camif_pad_reg_reset();

	rc = mt9d112_sensor_init_probe(data);
	if (rc < 0) {
		CDBG("mt9d112_sensor_init failed!\n");
		goto init_fail;
	}

init_done:
	return rc;

init_fail:
	kfree(mt9d112_ctrl);
	return rc;
}