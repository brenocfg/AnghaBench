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
struct power_supply {int dummy; } ;
struct ds2760_device_info {int /*<<< orphan*/  set_charged_work; int /*<<< orphan*/  monitor_wqueue; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct ds2760_device_info* to_ds2760_device_info (struct power_supply*) ; 

__attribute__((used)) static void ds2760_battery_set_charged(struct power_supply *psy)
{
	struct ds2760_device_info *di = to_ds2760_device_info(psy);

	/* postpone the actual work by 20 secs. This is for debouncing GPIO
	 * signals and to let the current value settle. See AN4188. */
	cancel_delayed_work(&di->set_charged_work);
	queue_delayed_work(di->monitor_wqueue, &di->set_charged_work, HZ * 20);
}