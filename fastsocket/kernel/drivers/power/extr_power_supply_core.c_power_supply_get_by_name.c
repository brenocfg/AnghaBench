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
struct device {int dummy; } ;

/* Variables and functions */
 struct device* class_find_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct power_supply* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  power_supply_class ; 
 int /*<<< orphan*/  power_supply_match_device_by_name ; 

struct power_supply *power_supply_get_by_name(char *name)
{
	struct device *dev = class_find_device(power_supply_class, NULL, name,
					power_supply_match_device_by_name);

	return dev ? dev_get_drvdata(dev) : NULL;
}