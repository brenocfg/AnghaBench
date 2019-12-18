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
struct power_supply {int /*<<< orphan*/  online_trig_name; int /*<<< orphan*/  online_trig; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_trigger_unregister_simple (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void power_supply_remove_gen_triggers(struct power_supply *psy)
{
	led_trigger_unregister_simple(psy->online_trig);
	kfree(psy->online_trig_name);
}