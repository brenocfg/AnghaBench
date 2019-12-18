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
struct device {TYPE_2__* p; } ;
struct bus_type {TYPE_1__* p; } ;
struct TYPE_4__ {int /*<<< orphan*/  knode_bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  klist_devices; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  klist_iter_exit (struct klist_iter*) ; 
 int /*<<< orphan*/  klist_iter_init_node (int /*<<< orphan*/ *,struct klist_iter*,int /*<<< orphan*/ *) ; 
 struct device* next_device (struct klist_iter*) ; 

int bus_for_each_dev(struct bus_type *bus, struct device *start,
		     void *data, int (*fn)(struct device *, void *))
{
	struct klist_iter i;
	struct device *dev;
	int error = 0;

	if (!bus)
		return -EINVAL;

	klist_iter_init_node(&bus->p->klist_devices, &i,
			     (start ? &start->p->knode_bus : NULL));
	while ((dev = next_device(&i)) && !error)
		error = fn(dev, data);
	klist_iter_exit(&i);
	return error;
}