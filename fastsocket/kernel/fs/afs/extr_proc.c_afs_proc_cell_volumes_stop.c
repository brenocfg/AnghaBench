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
struct afs_cell {int /*<<< orphan*/  vl_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void afs_proc_cell_volumes_stop(struct seq_file *p, void *v)
{
	struct afs_cell *cell = p->private;

	up_read(&cell->vl_sem);
}