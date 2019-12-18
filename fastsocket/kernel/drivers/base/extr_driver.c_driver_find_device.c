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
struct klist_iter {int dummy; } ;
struct device_driver {TYPE_1__* p; } ;
struct device {TYPE_2__* p; } ;
struct TYPE_4__ {int /*<<< orphan*/  knode_driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  klist_devices; } ;

/* Variables and functions */
 scalar_t__ get_device (struct device*) ; 
 int /*<<< orphan*/  klist_iter_exit (struct klist_iter*) ; 
 int /*<<< orphan*/  klist_iter_init_node (int /*<<< orphan*/ *,struct klist_iter*,int /*<<< orphan*/ *) ; 
 struct device* next_device (struct klist_iter*) ; 

struct device *driver_find_device(struct device_driver *drv,
				  struct device *start, void *data,
				  int (*match)(struct device *dev, void *data))
{
	struct klist_iter i;
	struct device *dev;

	if (!drv)
		return NULL;

	klist_iter_init_node(&drv->p->klist_devices, &i,
			     (start ? &start->p->knode_driver : NULL));
	while ((dev = next_device(&i)))
		if (match(dev, data) && get_device(dev))
			break;
	klist_iter_exit(&i);
	return dev;
}