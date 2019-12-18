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
struct wl1271 {int /*<<< orphan*/  nvs_loading_complete; struct platform_device* pdev; int /*<<< orphan*/ * dev; int /*<<< orphan*/  ptable; int /*<<< orphan*/  ops; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FW_ACTION_HOTPLUG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  WL12XX_NVS_NAME ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct wl1271*) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct wl1271*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_error (char*,int) ; 
 int /*<<< orphan*/  wlcore_nvs_cb ; 

int wlcore_probe(struct wl1271 *wl, struct platform_device *pdev)
{
	int ret;

	if (!wl->ops || !wl->ptable)
		return -EINVAL;

	wl->dev = &pdev->dev;
	wl->pdev = pdev;
	platform_set_drvdata(pdev, wl);

	ret = request_firmware_nowait(THIS_MODULE, FW_ACTION_HOTPLUG,
				      WL12XX_NVS_NAME, &pdev->dev, GFP_KERNEL,
				      wl, wlcore_nvs_cb);
	if (ret < 0) {
		wl1271_error("request_firmware_nowait failed: %d", ret);
		complete_all(&wl->nvs_loading_complete);
	}

	return ret;
}