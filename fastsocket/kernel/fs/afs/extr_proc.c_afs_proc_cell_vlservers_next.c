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
struct afs_cell {size_t vl_naddrs; void* vl_addrs; } ;
typedef  size_t loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,struct afs_cell*,size_t,size_t) ; 

__attribute__((used)) static void *afs_proc_cell_vlservers_next(struct seq_file *p, void *v,
					  loff_t *_pos)
{
	struct afs_cell *cell = p->private;
	loff_t pos;

	_enter("cell=%p{nad=%u} pos=%Ld", cell, cell->vl_naddrs, *_pos);

	pos = *_pos;
	(*_pos)++;
	if (pos >= cell->vl_naddrs)
		return NULL;

	return &cell->vl_addrs[pos];
}