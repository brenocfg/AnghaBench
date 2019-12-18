#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct msm_camera_sensor_info* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct msm_camera_sensor_info {struct msm_camera_device_platform_data* pdata; } ;
struct msm_camera_device_platform_data {int /*<<< orphan*/  (* camera_gpio_off ) () ;} ;
struct TYPE_4__ {int /*<<< orphan*/  appsz; int /*<<< orphan*/  appphy; int /*<<< orphan*/  mdcsz; int /*<<< orphan*/  mdcphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAMIO_MDC_CLK ; 
 int /*<<< orphan*/  CAMIO_VFE_CLK ; 
 int /*<<< orphan*/  CAMIO_VFE_MDC_CLK ; 
 int /*<<< orphan*/  appbase ; 
 TYPE_2__ camio_ext ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdcbase ; 
 int /*<<< orphan*/  msm_camio_clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

void msm_camio_disable(struct platform_device *pdev)
{
	struct msm_camera_sensor_info *sinfo = pdev->dev.platform_data;
	struct msm_camera_device_platform_data *camdev = sinfo->pdata;

	iounmap(mdcbase);
	release_mem_region(camio_ext.mdcphy, camio_ext.mdcsz);
	iounmap(appbase);
	release_mem_region(camio_ext.appphy, camio_ext.appsz);

	camdev->camera_gpio_off();

	msm_camio_clk_disable(CAMIO_VFE_CLK);
	msm_camio_clk_disable(CAMIO_MDC_CLK);
	msm_camio_clk_disable(CAMIO_VFE_MDC_CLK);
}