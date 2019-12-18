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
struct platform_device {int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct msm_camera_sensor_info {struct msm_camera_device_platform_data* pdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  appsz; int /*<<< orphan*/  appphy; int /*<<< orphan*/  mdcsz; int /*<<< orphan*/  mdcphy; } ;
struct msm_camera_device_platform_data {int /*<<< orphan*/  (* camera_gpio_on ) () ;TYPE_2__ ioext; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAMIO_MDC_CLK ; 
 int /*<<< orphan*/  CAMIO_VFE_CLK ; 
 int /*<<< orphan*/  CAMIO_VFE_MDC_CLK ; 
 int EBUSY ; 
 int ENOMEM ; 
 void* appbase ; 
 void* appio ; 
 TYPE_2__ camio_ext ; 
 void* ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 void* mdcbase ; 
 void* mdcio ; 
 int /*<<< orphan*/  msm_camio_clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

int msm_camio_enable(struct platform_device *pdev)
{
	int rc = 0;
	struct msm_camera_sensor_info *sinfo = pdev->dev.platform_data;
	struct msm_camera_device_platform_data *camdev = sinfo->pdata;

	camio_ext = camdev->ioext;

	appio = request_mem_region(camio_ext.appphy,
		camio_ext.appsz, pdev->name);
	if (!appio) {
		rc = -EBUSY;
		goto enable_fail;
	}

	appbase = ioremap(camio_ext.appphy,
		camio_ext.appsz);
	if (!appbase) {
		rc = -ENOMEM;
		goto apps_no_mem;
	}

	mdcio = request_mem_region(camio_ext.mdcphy,
		camio_ext.mdcsz, pdev->name);
	if (!mdcio) {
		rc = -EBUSY;
		goto mdc_busy;
	}

	mdcbase = ioremap(camio_ext.mdcphy,
		camio_ext.mdcsz);
	if (!mdcbase) {
		rc = -ENOMEM;
		goto mdc_no_mem;
	}

	camdev->camera_gpio_on();

	msm_camio_clk_enable(CAMIO_VFE_CLK);
	msm_camio_clk_enable(CAMIO_MDC_CLK);
	msm_camio_clk_enable(CAMIO_VFE_MDC_CLK);
	return 0;

mdc_no_mem:
	release_mem_region(camio_ext.mdcphy, camio_ext.mdcsz);
mdc_busy:
	iounmap(appbase);
apps_no_mem:
	release_mem_region(camio_ext.appphy, camio_ext.appsz);
enable_fail:
	return rc;
}