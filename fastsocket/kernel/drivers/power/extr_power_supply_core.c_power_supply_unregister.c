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
struct power_supply {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  power_supply_remove_attrs (struct power_supply*) ; 
 int /*<<< orphan*/  power_supply_remove_triggers (struct power_supply*) ; 

void power_supply_unregister(struct power_supply *psy)
{
	flush_scheduled_work();
	power_supply_remove_triggers(psy);
	power_supply_remove_attrs(psy);
	device_unregister(psy->dev);
}