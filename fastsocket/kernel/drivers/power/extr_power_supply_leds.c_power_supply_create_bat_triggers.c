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
struct power_supply {void* charging_full_trig_name; void* charging_trig_name; int /*<<< orphan*/  full_trig; void* full_trig_name; int /*<<< orphan*/  charging_trig; int /*<<< orphan*/  charging_full_trig; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  led_trigger_register_simple (void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int power_supply_create_bat_triggers(struct power_supply *psy)
{
	int rc = 0;

	psy->charging_full_trig_name = kasprintf(GFP_KERNEL,
					"%s-charging-or-full", psy->name);
	if (!psy->charging_full_trig_name)
		goto charging_full_failed;

	psy->charging_trig_name = kasprintf(GFP_KERNEL,
					"%s-charging", psy->name);
	if (!psy->charging_trig_name)
		goto charging_failed;

	psy->full_trig_name = kasprintf(GFP_KERNEL, "%s-full", psy->name);
	if (!psy->full_trig_name)
		goto full_failed;

	led_trigger_register_simple(psy->charging_full_trig_name,
				    &psy->charging_full_trig);
	led_trigger_register_simple(psy->charging_trig_name,
				    &psy->charging_trig);
	led_trigger_register_simple(psy->full_trig_name,
				    &psy->full_trig);

	goto success;

full_failed:
	kfree(psy->charging_trig_name);
charging_failed:
	kfree(psy->charging_full_trig_name);
charging_full_failed:
	rc = -ENOMEM;
success:
	return rc;
}