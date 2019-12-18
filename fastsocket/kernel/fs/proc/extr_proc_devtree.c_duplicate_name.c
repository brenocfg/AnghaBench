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
struct proc_dir_entry {int /*<<< orphan*/  name; struct proc_dir_entry* next; struct proc_dir_entry* subdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_subdir_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int duplicate_name(struct proc_dir_entry *de, const char *name)
{
	struct proc_dir_entry *ent;
	int found = 0;

	spin_lock(&proc_subdir_lock);

	for (ent = de->subdir; ent != NULL; ent = ent->next) {
		if (strcmp(ent->name, name) == 0) {
			found = 1;
			break;
		}
	}

	spin_unlock(&proc_subdir_lock);

	return found;
}