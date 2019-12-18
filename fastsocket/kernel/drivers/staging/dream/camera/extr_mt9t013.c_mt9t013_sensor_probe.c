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
 int ENOTSUPP ; 
 int /*<<< orphan*/  MT9T013_DEFAULT_CLOCK_RATE ; 
 int i2c_add_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_del_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msm_camio_clk_rate_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mt9t013_client ; 
 int /*<<< orphan*/  mt9t013_i2c_driver ; 
 int mt9t013_probe_init_sensor (struct msm_camera_sensor_info const*) ; 
 int /*<<< orphan*/  mt9t013_sensor_config ; 
 int /*<<< orphan*/  mt9t013_sensor_init_done (struct msm_camera_sensor_info const*) ; 
 int /*<<< orphan*/  mt9t013_sensor_open_init ; 
 int /*<<< orphan*/  mt9t013_sensor_release ; 

__attribute__((used)) static int mt9t013_sensor_probe(
		const struct msm_camera_sensor_info *info,
		struct msm_sensor_ctrl *s)
{
	/* We expect this driver to match with the i2c device registered
	 * in the board file immediately. */
	int rc = i2c_add_driver(&mt9t013_i2c_driver);
	if (rc < 0 || mt9t013_client == NULL) {
		rc = -ENOTSUPP;
		goto probe_done;
	}

	/* enable mclk first */
	msm_camio_clk_rate_set(MT9T013_DEFAULT_CLOCK_RATE);
	mdelay(20);

	rc = mt9t013_probe_init_sensor(info);
	if (rc < 0) {
		i2c_del_driver(&mt9t013_i2c_driver);
		goto probe_done;
	}

	s->s_init = mt9t013_sensor_open_init;
	s->s_release = mt9t013_sensor_release;
	s->s_config  = mt9t013_sensor_config;
	mt9t013_sensor_init_done(info);

probe_done:
	return rc;
}