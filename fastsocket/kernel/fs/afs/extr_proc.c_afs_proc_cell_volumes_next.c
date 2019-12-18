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
struct seq_file {struct afs_cell* private; } ;
struct afs_cell {int /*<<< orphan*/  vl_list; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,struct afs_cell*,int /*<<< orphan*/ ) ; 
 void* seq_list_next (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *afs_proc_cell_volumes_next(struct seq_file *p, void *v,
					loff_t *_pos)
{
	struct afs_cell *cell = p->private;

	_enter("cell=%p pos=%Ld", cell, *_pos);
	return seq_list_next(v, &cell->vl_list, _pos);
}