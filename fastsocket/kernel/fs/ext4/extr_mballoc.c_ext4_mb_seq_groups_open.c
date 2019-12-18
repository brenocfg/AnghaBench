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
struct super_block {int dummy; } ;
struct seq_file {struct super_block* private; } ;
struct inode {int dummy; } ;
struct file {scalar_t__ private_data; } ;
struct TYPE_2__ {struct super_block* data; } ;

/* Variables and functions */
 TYPE_1__* PDE (struct inode*) ; 
 int /*<<< orphan*/  ext4_mb_seq_groups_ops ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ext4_mb_seq_groups_open(struct inode *inode, struct file *file)
{
	struct super_block *sb = PDE(inode)->data;
	int rc;

	rc = seq_open(file, &ext4_mb_seq_groups_ops);
	if (rc == 0) {
		struct seq_file *m = (struct seq_file *)file->private_data;
		m->private = sb;
	}
	return rc;

}