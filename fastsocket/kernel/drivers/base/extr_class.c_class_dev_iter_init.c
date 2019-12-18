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
struct klist_node {int dummy; } ;
struct device_type {int dummy; } ;
struct device {struct klist_node knode_class; } ;
struct class_dev_iter {struct device_type const* type; int /*<<< orphan*/  ki; } ;
struct class {TYPE_1__* p; } ;
struct TYPE_2__ {int /*<<< orphan*/  class_devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  klist_iter_init_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct klist_node*) ; 

void class_dev_iter_init(struct class_dev_iter *iter, struct class *class,
			 struct device *start, const struct device_type *type)
{
	struct klist_node *start_knode = NULL;

	if (start)
		start_knode = &start->knode_class;
	klist_iter_init_node(&class->p->class_devices, &iter->ki, start_knode);
	iter->type = type;
}