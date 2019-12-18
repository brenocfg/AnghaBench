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
struct kset_uevent_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * kset; int /*<<< orphan*/ * ktype; struct kobject* parent; } ;
struct kset {TYPE_1__ kobj; struct kset_uevent_ops* uevent_ops; } ;
struct kobject {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct kset*) ; 
 int kobject_set_name (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  kset_ktype ; 
 struct kset* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct kset *kset_create(const char *name,
				struct kset_uevent_ops *uevent_ops,
				struct kobject *parent_kobj)
{
	struct kset *kset;
	int retval;

	kset = kzalloc(sizeof(*kset), GFP_KERNEL);
	if (!kset)
		return NULL;
	retval = kobject_set_name(&kset->kobj, name);
	if (retval) {
		kfree(kset);
		return NULL;
	}
	kset->uevent_ops = uevent_ops;
	kset->kobj.parent = parent_kobj;

	/*
	 * The kobject of this kset will have a type of kset_ktype and belong to
	 * no kset itself.  That way we can properly free it when it is
	 * finished being used.
	 */
	kset->kobj.ktype = &kset_ktype;
	kset->kobj.kset = NULL;

	return kset;
}