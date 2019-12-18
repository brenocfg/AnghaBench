#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct msm_sensor_ctrl {int /*<<< orphan*/  s_config; int /*<<< orphan*/  s_release; int /*<<< orphan*/  s_init; } ;
struct msm_camera_sensor_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*) ; 
 int ENOTSUPP ; 
 int i2c_add_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msm_camio_clk_rate_set (int) ; 
 int /*<<< orphan*/ * s5k3e2fx_client ; 
 int /*<<< orphan*/  s5k3e2fx_i2c_driver ; 
 int /*<<< orphan*/  s5k3e2fx_probe_init_done (struct msm_camera_sensor_info const*) ; 
 int s5k3e2fx_probe_init_sensor (struct msm_camera_sensor_info const*) ; 
 int /*<<< orphan*/  s5k3e2fx_sensor_config ; 
 int /*<<< orphan*/  s5k3e2fx_sensor_open_init ; 
 int /*<<< orphan*/  s5k3e2fx_sensor_release ; 

__attribute__((used)) static int s5k3e2fx_sensor_probe(const struct msm_camera_sensor_info *info,
		struct msm_sensor_ctrl *s)
{
	int rc = 0;

	rc = i2c_add_driver(&s5k3e2fx_i2c_driver);
	if (rc < 0 || s5k3e2fx_client == NULL) {
		rc = -ENOTSUPP;
		goto probe_fail;
	}

	msm_camio_clk_rate_set(24000000);
	mdelay(20);

	rc = s5k3e2fx_probe_init_sensor(info);
	if (rc < 0)
		goto probe_fail;

	s->s_init = s5k3e2fx_sensor_open_init;
	s->s_release = s5k3e2fx_sensor_release;
	s->s_config  = s5k3e2fx_sensor_config;
	s5k3e2fx_probe_init_done(info);

	return rc;

probe_fail:
	CDBG("SENSOR PROBE FAILS!\n");
	return rc;
}