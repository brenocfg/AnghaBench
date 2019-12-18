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
struct power_supply {int num_supplicants; scalar_t__ (* get_property ) (struct power_supply*,int /*<<< orphan*/ ,union power_supply_propval*) ;int /*<<< orphan*/  name; int /*<<< orphan*/ * supplied_to; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_SUPPLY_PROP_ONLINE ; 
 struct power_supply* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct power_supply*,int /*<<< orphan*/ ,union power_supply_propval*) ; 

__attribute__((used)) static int __power_supply_am_i_supplied(struct device *dev, void *data)
{
	union power_supply_propval ret = {0,};
	struct power_supply *psy = (struct power_supply *)data;
	struct power_supply *epsy = dev_get_drvdata(dev);
	int i;

	for (i = 0; i < epsy->num_supplicants; i++) {
		if (!strcmp(epsy->supplied_to[i], psy->name)) {
			if (epsy->get_property(epsy,
				  POWER_SUPPLY_PROP_ONLINE, &ret))
				continue;
			if (ret.intval)
				return ret.intval;
		}
	}
	return 0;
}