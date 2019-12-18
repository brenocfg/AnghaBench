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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int msm_camera_drv_start (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9t013_sensor_probe ; 

__attribute__((used)) static int __mt9t013_probe(struct platform_device *pdev)
{
	return msm_camera_drv_start(pdev, mt9t013_sensor_probe);
}