#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device_driver {TYPE_1__* p; } ;
struct attribute_group {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int sysfs_create_group (int /*<<< orphan*/ *,struct attribute_group const*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,struct attribute_group const*) ; 

__attribute__((used)) static int driver_add_groups(struct device_driver *drv,
			     const struct attribute_group **groups)
{
	int error = 0;
	int i;

	if (groups) {
		for (i = 0; groups[i]; i++) {
			error = sysfs_create_group(&drv->p->kobj, groups[i]);
			if (error) {
				while (--i >= 0)
					sysfs_remove_group(&drv->p->kobj,
							   groups[i]);
				break;
			}
		}
	}
	return error;
}