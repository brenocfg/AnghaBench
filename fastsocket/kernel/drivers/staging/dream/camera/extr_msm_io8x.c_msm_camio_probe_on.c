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
struct TYPE_2__ {struct msm_camera_sensor_info* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct msm_camera_sensor_info {struct msm_camera_device_platform_data* pdata; } ;
struct msm_camera_device_platform_data {int /*<<< orphan*/  (* camera_gpio_on ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAMIO_VFE_MDC_CLK ; 
 int msm_camio_clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

int msm_camio_probe_on(struct platform_device *pdev)
{
	struct msm_camera_sensor_info *sinfo = pdev->dev.platform_data;
	struct msm_camera_device_platform_data *camdev = sinfo->pdata;

	camdev->camera_gpio_on();
	return msm_camio_clk_enable(CAMIO_VFE_MDC_CLK);
}