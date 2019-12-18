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
struct power_supply {int num_supplicants; int /*<<< orphan*/  (* external_power_changed ) (struct power_supply*) ;int /*<<< orphan*/  name; int /*<<< orphan*/ * supplied_to; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct power_supply* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct power_supply*) ; 

__attribute__((used)) static int __power_supply_changed_work(struct device *dev, void *data)
{
	struct power_supply *psy = (struct power_supply *)data;
	struct power_supply *pst = dev_get_drvdata(dev);
	int i;

	for (i = 0; i < psy->num_supplicants; i++)
		if (!strcmp(psy->supplied_to[i], pst->name)) {
			if (pst->external_power_changed)
				pst->external_power_changed(pst);
		}
	return 0;
}