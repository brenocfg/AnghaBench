#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct seq_file {struct afs_cell* private; } ;
struct inode {int dummy; } ;
struct file {struct seq_file* private_data; } ;
struct afs_cell {int dummy; } ;
struct TYPE_2__ {struct afs_cell* data; } ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_1__* PDE (struct inode*) ; 
 int /*<<< orphan*/  afs_proc_cell_vlservers_ops ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int afs_proc_cell_vlservers_open(struct inode *inode, struct file *file)
{
	struct afs_cell *cell;
	struct seq_file *m;
	int ret;

	cell = PDE(inode)->data;
	if (!cell)
		return -ENOENT;

	ret = seq_open(file, &afs_proc_cell_vlservers_ops);
	if (ret<0)
		return ret;

	m = file->private_data;
	m->private = cell;

	return 0;
}