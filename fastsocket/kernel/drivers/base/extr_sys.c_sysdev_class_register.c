#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* kset; int /*<<< orphan*/ * ktype; int /*<<< orphan*/ * parent; } ;
struct TYPE_7__ {TYPE_2__ kobj; } ;
struct sysdev_class {TYPE_3__ kset; int /*<<< orphan*/  name; int /*<<< orphan*/  drivers; } ;
struct kobject {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int kobject_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int kset_register (TYPE_3__*) ; 
 int /*<<< orphan*/  ktype_sysdev_class ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* system_kset ; 

int sysdev_class_register(struct sysdev_class *cls)
{
	int retval;

	pr_debug("Registering sysdev class '%s'\n", cls->name);

	INIT_LIST_HEAD(&cls->drivers);
	memset(&cls->kset.kobj, 0x00, sizeof(struct kobject));
	cls->kset.kobj.parent = &system_kset->kobj;
	cls->kset.kobj.ktype = &ktype_sysdev_class;
	cls->kset.kobj.kset = system_kset;

	retval = kobject_set_name(&cls->kset.kobj, "%s", cls->name);
	if (retval)
		return retval;

	return kset_register(&cls->kset);
}