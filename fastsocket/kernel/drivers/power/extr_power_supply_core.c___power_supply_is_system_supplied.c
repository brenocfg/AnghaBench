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
union power_supply_propval {int intval; int /*<<< orphan*/  member_0; } ;
struct power_supply {scalar_t__ type; scalar_t__ (* get_property ) (struct power_supply*,int /*<<< orphan*/ ,union power_supply_propval*) ;} ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_SUPPLY_PROP_ONLINE ; 
 scalar_t__ POWER_SUPPLY_TYPE_BATTERY ; 
 struct power_supply* dev_get_drvdata (struct device*) ; 
 scalar_t__ stub1 (struct power_supply*,int /*<<< orphan*/ ,union power_supply_propval*) ; 

__attribute__((used)) static int __power_supply_is_system_supplied(struct device *dev, void *data)
{
	union power_supply_propval ret = {0,};
	struct power_supply *psy = dev_get_drvdata(dev);

	if (psy->type != POWER_SUPPLY_TYPE_BATTERY) {
		if (psy->get_property(psy, POWER_SUPPLY_PROP_ONLINE, &ret))
			return 0;
		if (ret.intval)
			return ret.intval;
	}
	return 0;
}