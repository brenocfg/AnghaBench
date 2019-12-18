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
struct afs_cell {size_t vl_naddrs; void* vl_addrs; int /*<<< orphan*/  vl_sem; } ;
typedef  size_t loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,struct afs_cell*,size_t) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *afs_proc_cell_vlservers_start(struct seq_file *m, loff_t *_pos)
{
	struct afs_cell *cell = m->private;
	loff_t pos = *_pos;

	_enter("cell=%p pos=%Ld", cell, *_pos);

	/* lock the list against modification */
	down_read(&cell->vl_sem);

	/* allow for the header line */
	if (!pos)
		return (void *) 1;
	pos--;

	if (pos >= cell->vl_naddrs)
		return NULL;

	return &cell->vl_addrs[pos];
}