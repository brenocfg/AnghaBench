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
struct kobject {int dummy; } ;
struct driver_private {struct device_driver* driver; } ;
struct device_driver {TYPE_1__* p; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 struct kobject* kobject_get (int /*<<< orphan*/ *) ; 
 struct driver_private* to_driver (struct kobject*) ; 

struct device_driver *get_driver(struct device_driver *drv)
{
	if (drv) {
		struct driver_private *priv;
		struct kobject *kobj;

		kobj = kobject_get(&drv->p->kobj);
		priv = to_driver(kobj);
		return priv->driver;
	}
	return NULL;
}