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
struct power_supply {int num_properties; size_t* properties; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * power_supply_attrs ; 
 int /*<<< orphan*/ * power_supply_static_attrs ; 

void power_supply_remove_attrs(struct power_supply *psy)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(power_supply_static_attrs); i++)
		device_remove_file(psy->dev, &power_supply_static_attrs[i]);

	for (i = 0; i < psy->num_properties; i++)
		device_remove_file(psy->dev,
			    &power_supply_attrs[psy->properties[i]]);
}