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
struct mmc_host {int /*<<< orphan*/  led; int /*<<< orphan*/  class_dev; int /*<<< orphan*/  pm_notify; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_trigger_unregister_simple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_remove_host_debugfs (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_stop_host (struct mmc_host*) ; 
 int /*<<< orphan*/  unregister_pm_notifier (int /*<<< orphan*/ *) ; 

void mmc_remove_host(struct mmc_host *host)
{
	unregister_pm_notifier(&host->pm_notify);
	mmc_stop_host(host);

#ifdef CONFIG_DEBUG_FS
	mmc_remove_host_debugfs(host);
#endif

	device_del(&host->class_dev);

	led_trigger_unregister_simple(host->led);

}