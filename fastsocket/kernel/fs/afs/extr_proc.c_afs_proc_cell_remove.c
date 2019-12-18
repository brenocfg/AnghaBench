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
struct afs_cell {char* name; int /*<<< orphan*/  proc_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  proc_afs ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ ) ; 

void afs_proc_cell_remove(struct afs_cell *cell)
{
	_enter("");

	remove_proc_entry("volumes", cell->proc_dir);
	remove_proc_entry("vlservers", cell->proc_dir);
	remove_proc_entry("servers", cell->proc_dir);
	remove_proc_entry(cell->name, proc_afs);

	_leave("");
}