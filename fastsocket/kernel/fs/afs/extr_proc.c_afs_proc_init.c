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
struct proc_dir_entry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_proc_cells_fops ; 
 int /*<<< orphan*/  afs_proc_rootcell_fops ; 
 int /*<<< orphan*/ * proc_afs ; 
 struct proc_dir_entry* proc_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * proc_mkdir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ *) ; 

int afs_proc_init(void)
{
	struct proc_dir_entry *p;

	_enter("");

	proc_afs = proc_mkdir("fs/afs", NULL);
	if (!proc_afs)
		goto error_dir;

	p = proc_create("cells", 0, proc_afs, &afs_proc_cells_fops);
	if (!p)
		goto error_cells;

	p = proc_create("rootcell", 0, proc_afs, &afs_proc_rootcell_fops);
	if (!p)
		goto error_rootcell;

	_leave(" = 0");
	return 0;

error_rootcell:
 	remove_proc_entry("cells", proc_afs);
error_cells:
	remove_proc_entry("fs/afs", NULL);
error_dir:
	_leave(" = -ENOMEM");
	return -ENOMEM;
}