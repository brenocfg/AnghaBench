#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  kobj; TYPE_2__* driver; } ;
struct TYPE_4__ {TYPE_1__* p; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 char* kobject_name (int /*<<< orphan*/ *) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int driver_sysfs_add(struct device *dev)
{
	int ret;

	ret = sysfs_create_link(&dev->driver->p->kobj, &dev->kobj,
			  kobject_name(&dev->kobj));
	if (ret == 0) {
		ret = sysfs_create_link(&dev->kobj, &dev->driver->p->kobj,
					"driver");
		if (ret)
			sysfs_remove_link(&dev->driver->p->kobj,
					kobject_name(&dev->kobj));
	}
	return ret;
}