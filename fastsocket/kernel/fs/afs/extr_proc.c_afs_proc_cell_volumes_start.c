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
struct afs_cell {int /*<<< orphan*/  vl_list; int /*<<< orphan*/  vl_sem; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,struct afs_cell*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 void* seq_list_start_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *afs_proc_cell_volumes_start(struct seq_file *m, loff_t *_pos)
{
	struct afs_cell *cell = m->private;

	_enter("cell=%p pos=%Ld", cell, *_pos);

	/* lock the list against modification */
	down_read(&cell->vl_sem);
	return seq_list_start_head(&cell->vl_list, *_pos);
}