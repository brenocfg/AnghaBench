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
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,struct proc_dir_entry*) ; 

__attribute__((used)) static void i2o_proc_subdir_remove(struct proc_dir_entry *dir)
{
	struct proc_dir_entry *pe, *tmp;
	pe = dir->subdir;
	while (pe) {
		tmp = pe->next;
		i2o_proc_subdir_remove(pe);
		remove_proc_entry(pe->name, dir);
		pe = tmp;
	}
}