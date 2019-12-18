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
struct kobject {int dummy; } ;
struct hstate {int /*<<< orphan*/  name; } ;
struct attribute_group {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct hstate* hstates ; 
 struct kobject* kobject_create_and_add (int /*<<< orphan*/ ,struct kobject*) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 int sysfs_create_group (struct kobject*,struct attribute_group*) ; 

__attribute__((used)) static int hugetlb_sysfs_add_hstate(struct hstate *h, struct kobject *parent,
				    struct kobject **hstate_kobjs,
				    struct attribute_group *hstate_attr_group)
{
	int retval;
	int hi = h - hstates;

	hstate_kobjs[hi] = kobject_create_and_add(h->name, parent);
	if (!hstate_kobjs[hi])
		return -ENOMEM;

	retval = sysfs_create_group(hstate_kobjs[hi], hstate_attr_group);
	if (retval)
		kobject_put(hstate_kobjs[hi]);

	return retval;
}