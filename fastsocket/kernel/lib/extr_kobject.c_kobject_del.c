#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kobject {int /*<<< orphan*/ * parent; scalar_t__ state_in_sysfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobj_kset_leave (struct kobject*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_dir (struct kobject*) ; 

void kobject_del(struct kobject *kobj)
{
	if (!kobj)
		return;

	sysfs_remove_dir(kobj);
	kobj->state_in_sysfs = 0;
	kobj_kset_leave(kobj);
	kobject_put(kobj->parent);
	kobj->parent = NULL;
}