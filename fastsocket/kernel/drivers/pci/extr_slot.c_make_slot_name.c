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

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 struct kobject* kset_find_obj (int /*<<< orphan*/ ,char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_slots_kset ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *make_slot_name(const char *name)
{
	char *new_name;
	int len, max, dup;

	new_name = kstrdup(name, GFP_KERNEL);
	if (!new_name)
		return NULL;

	/*
	 * Make sure we hit the realloc case the first time through the
	 * loop.  'len' will be strlen(name) + 3 at that point which is
	 * enough space for "name-X" and the trailing NUL.
	 */
	len = strlen(name) + 2;
	max = 1;
	dup = 1;

	for (;;) {
		struct kobject *dup_slot;
		dup_slot = kset_find_obj(pci_slots_kset, new_name);
		if (!dup_slot)
			break;
		kobject_put(dup_slot);
		if (dup == max) {
			len++;
			max *= 10;
			kfree(new_name);
			new_name = kmalloc(len, GFP_KERNEL);
			if (!new_name)
				break;
		}
		sprintf(new_name, "%s-%d", name, dup++);
	}

	return new_name;
}