#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_4__ {TYPE_1__* fat_inode; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 TYPE_2__* MSDOS_SB (int /*<<< orphan*/ ) ; 
 int simple_fsync (struct file*,struct dentry*,int) ; 
 int sync_mapping_buffers (int /*<<< orphan*/ ) ; 

int fat_file_fsync(struct file *filp, struct dentry *dentry, int datasync)
{
	struct inode *inode = dentry->d_inode;
	int res, err;

	res = simple_fsync(filp, dentry, datasync);
	err = sync_mapping_buffers(MSDOS_SB(inode->i_sb)->fat_inode->i_mapping);

	return res ? res : err;
}