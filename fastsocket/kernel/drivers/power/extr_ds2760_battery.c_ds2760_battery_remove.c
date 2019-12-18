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
struct ds2760_device_info {int /*<<< orphan*/  bat; int /*<<< orphan*/  monitor_wqueue; int /*<<< orphan*/  set_charged_work; int /*<<< orphan*/  monitor_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_rearming_delayed_workqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 struct ds2760_device_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ds2760_battery_remove(struct platform_device *pdev)
{
	struct ds2760_device_info *di = platform_get_drvdata(pdev);

	cancel_rearming_delayed_workqueue(di->monitor_wqueue,
					  &di->monitor_work);
	cancel_rearming_delayed_workqueue(di->monitor_wqueue,
					  &di->set_charged_work);
	destroy_workqueue(di->monitor_wqueue);
	power_supply_unregister(&di->bat);

	return 0;
}