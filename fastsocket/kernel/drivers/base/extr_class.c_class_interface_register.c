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
struct device {int dummy; } ;
struct class_interface {int /*<<< orphan*/  (* add_dev ) (struct device*,struct class_interface*) ;int /*<<< orphan*/  node; int /*<<< orphan*/  class; } ;
struct class_dev_iter {int dummy; } ;
struct class {TYPE_1__* p; } ;
struct TYPE_2__ {int /*<<< orphan*/  class_mutex; int /*<<< orphan*/  class_interfaces; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  class_dev_iter_exit (struct class_dev_iter*) ; 
 int /*<<< orphan*/  class_dev_iter_init (struct class_dev_iter*,struct class*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct device* class_dev_iter_next (struct class_dev_iter*) ; 
 struct class* class_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct device*,struct class_interface*) ; 

int class_interface_register(struct class_interface *class_intf)
{
	struct class *parent;
	struct class_dev_iter iter;
	struct device *dev;

	if (!class_intf || !class_intf->class)
		return -ENODEV;

	parent = class_get(class_intf->class);
	if (!parent)
		return -EINVAL;

	mutex_lock(&parent->p->class_mutex);
	list_add_tail(&class_intf->node, &parent->p->class_interfaces);
	if (class_intf->add_dev) {
		class_dev_iter_init(&iter, parent, NULL, NULL);
		while ((dev = class_dev_iter_next(&iter)))
			class_intf->add_dev(dev, class_intf);
		class_dev_iter_exit(&iter);
	}
	mutex_unlock(&parent->p->class_mutex);

	return 0;
}