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
struct proc_dir_entry {int /*<<< orphan*/  name; struct i2o_controller* data; struct proc_dir_entry* next; struct proc_dir_entry* subdir; } ;
struct i2o_controller {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2o_proc_subdir_remove (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  osm_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,struct proc_dir_entry*) ; 

__attribute__((used)) static void i2o_proc_iop_remove(struct proc_dir_entry *dir,
				struct i2o_controller *c)
{
	struct proc_dir_entry *pe, *tmp;

	pe = dir->subdir;
	while (pe) {
		tmp = pe->next;
		if (pe->data == c) {
			i2o_proc_subdir_remove(pe);
			remove_proc_entry(pe->name, dir);
		}
		osm_debug("removing IOP /proc/i2o/%s\n", c->name);
		pe = tmp;
	}
}