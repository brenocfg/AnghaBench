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
struct msm_camera_sensor_info {int /*<<< orphan*/  sensor_reset; } ;

/* Variables and functions */
 int gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int mt9d112_reset(const struct msm_camera_sensor_info *dev)
{
	int rc = 0;

	rc = gpio_request(dev->sensor_reset, "mt9d112");

	if (!rc) {
		rc = gpio_direction_output(dev->sensor_reset, 0);
		mdelay(20);
		rc = gpio_direction_output(dev->sensor_reset, 1);
	}

	gpio_free(dev->sensor_reset);
	return rc;
}