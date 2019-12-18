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
struct wl1271 {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; scalar_t__ irq_wake_enabled; int /*<<< orphan*/  initialized; int /*<<< orphan*/  nvs_loading_complete; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct wl1271*) ; 
 struct wl1271* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1271_unregister_hw (struct wl1271*) ; 
 int /*<<< orphan*/  wlcore_free_hw (struct wl1271*) ; 

int wlcore_remove(struct platform_device *pdev)
{
	struct wl1271 *wl = platform_get_drvdata(pdev);

	wait_for_completion(&wl->nvs_loading_complete);
	if (!wl->initialized)
		return 0;

	if (wl->irq_wake_enabled) {
		device_init_wakeup(wl->dev, 0);
		disable_irq_wake(wl->irq);
	}
	wl1271_unregister_hw(wl);
	free_irq(wl->irq, wl);
	wlcore_free_hw(wl);

	return 0;
}