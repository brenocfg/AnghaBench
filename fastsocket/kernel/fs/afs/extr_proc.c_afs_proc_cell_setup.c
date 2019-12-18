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
struct afs_cell {char* name; int /*<<< orphan*/  proc_dir; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  _enter (char*,struct afs_cell*,char*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_proc_cell_servers_fops ; 
 int /*<<< orphan*/  afs_proc_cell_vlservers_fops ; 
 int /*<<< orphan*/  afs_proc_cell_volumes_fops ; 
 int /*<<< orphan*/  proc_afs ; 
 struct proc_dir_entry* proc_create_data (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct afs_cell*) ; 
 int /*<<< orphan*/  proc_mkdir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ ) ; 

int afs_proc_cell_setup(struct afs_cell *cell)
{
	struct proc_dir_entry *p;

	_enter("%p{%s}", cell, cell->name);

	cell->proc_dir = proc_mkdir(cell->name, proc_afs);
	if (!cell->proc_dir)
		goto error_dir;

	p = proc_create_data("servers", 0, cell->proc_dir,
			     &afs_proc_cell_servers_fops, cell);
	if (!p)
		goto error_servers;

	p = proc_create_data("vlservers", 0, cell->proc_dir,
			     &afs_proc_cell_vlservers_fops, cell);
	if (!p)
		goto error_vlservers;

	p = proc_create_data("volumes", 0, cell->proc_dir,
			     &afs_proc_cell_volumes_fops, cell);
	if (!p)
		goto error_volumes;

	_leave(" = 0");
	return 0;

error_volumes:
	remove_proc_entry("vlservers", cell->proc_dir);
error_vlservers:
	remove_proc_entry("servers", cell->proc_dir);
error_servers:
	remove_proc_entry(cell->name, proc_afs);
error_dir:
	_leave(" = -ENOMEM");
	return -ENOMEM;
}