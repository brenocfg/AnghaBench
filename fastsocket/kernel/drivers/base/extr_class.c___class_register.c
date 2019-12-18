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
struct lock_class_key {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ktype; void* kset; } ;
struct TYPE_3__ {TYPE_2__ kobj; } ;
struct class_private {TYPE_1__ class_subsys; struct class* class; int /*<<< orphan*/  class_mutex; int /*<<< orphan*/  class_dirs; int /*<<< orphan*/  class_interfaces; int /*<<< orphan*/  class_devices; } ;
struct class {struct class_private* p; scalar_t__ dev_kobj; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __mutex_init (int /*<<< orphan*/ *,char*,struct lock_class_key*) ; 
 int add_class_attrs (int /*<<< orphan*/ ) ; 
 struct class block_class ; 
 int /*<<< orphan*/  class_get (struct class*) ; 
 void* class_kset ; 
 int /*<<< orphan*/  class_ktype ; 
 int /*<<< orphan*/  class_put (struct class*) ; 
 int /*<<< orphan*/  kfree (struct class_private*) ; 
 int /*<<< orphan*/  klist_class_dev_get ; 
 int /*<<< orphan*/  klist_class_dev_put ; 
 int /*<<< orphan*/  klist_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kobject_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kset_init (int /*<<< orphan*/ *) ; 
 int kset_register (TYPE_1__*) ; 
 struct class_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sysfs_dev_char_kobj ; 

int __class_register(struct class *cls, struct lock_class_key *key)
{
	struct class_private *cp;
	int error;

	pr_debug("device class '%s': registering\n", cls->name);

	cp = kzalloc(sizeof(*cp), GFP_KERNEL);
	if (!cp)
		return -ENOMEM;
	klist_init(&cp->class_devices, klist_class_dev_get, klist_class_dev_put);
	INIT_LIST_HEAD(&cp->class_interfaces);
	kset_init(&cp->class_dirs);
	__mutex_init(&cp->class_mutex, "struct class mutex", key);
	error = kobject_set_name(&cp->class_subsys.kobj, "%s", cls->name);
	if (error) {
		kfree(cp);
		return error;
	}

	/* set the default /sys/dev directory for devices of this class */
	if (!cls->dev_kobj)
		cls->dev_kobj = sysfs_dev_char_kobj;

#if defined(CONFIG_SYSFS_DEPRECATED) && defined(CONFIG_BLOCK)
	/* let the block class directory show up in the root of sysfs */
	if (cls != &block_class)
		cp->class_subsys.kobj.kset = class_kset;
#else
	cp->class_subsys.kobj.kset = class_kset;
#endif
	cp->class_subsys.kobj.ktype = &class_ktype;
	cp->class = cls;
	cls->p = cp;

	error = kset_register(&cp->class_subsys);
	if (error) {
		kfree(cp);
		return error;
	}
	error = add_class_attrs(class_get(cls));
	class_put(cls);
	return error;
}