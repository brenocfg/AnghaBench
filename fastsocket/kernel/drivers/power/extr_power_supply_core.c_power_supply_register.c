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
struct power_supply {int /*<<< orphan*/  dev; int /*<<< orphan*/  changed_work; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,struct power_supply*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_changed (struct power_supply*) ; 
 int /*<<< orphan*/  power_supply_changed_work ; 
 int /*<<< orphan*/  power_supply_class ; 
 int power_supply_create_attrs (struct power_supply*) ; 
 int power_supply_create_triggers (struct power_supply*) ; 
 int /*<<< orphan*/  power_supply_remove_attrs (struct power_supply*) ; 

int power_supply_register(struct device *parent, struct power_supply *psy)
{
	int rc = 0;

	psy->dev = device_create(power_supply_class, parent, 0, psy,
				 "%s", psy->name);
	if (IS_ERR(psy->dev)) {
		rc = PTR_ERR(psy->dev);
		goto dev_create_failed;
	}

	INIT_WORK(&psy->changed_work, power_supply_changed_work);

	rc = power_supply_create_attrs(psy);
	if (rc)
		goto create_attrs_failed;

	rc = power_supply_create_triggers(psy);
	if (rc)
		goto create_triggers_failed;

	power_supply_changed(psy);

	goto success;

create_triggers_failed:
	power_supply_remove_attrs(psy);
create_attrs_failed:
	device_unregister(psy->dev);
dev_create_failed:
success:
	return rc;
}