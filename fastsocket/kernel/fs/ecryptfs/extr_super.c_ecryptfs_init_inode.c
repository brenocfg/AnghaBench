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
struct inode {TYPE_1__* i_mapping; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_version; int /*<<< orphan*/  i_ino; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ecryptfs_aops ; 
 int /*<<< orphan*/  ecryptfs_main_fops ; 
 int /*<<< orphan*/  ecryptfs_main_iops ; 
 int /*<<< orphan*/  ecryptfs_set_inode_lower (struct inode*,struct inode*) ; 

void ecryptfs_init_inode(struct inode *inode, struct inode *lower_inode)
{
	ecryptfs_set_inode_lower(inode, lower_inode);
	inode->i_ino = lower_inode->i_ino;
	inode->i_version++;
	inode->i_op = &ecryptfs_main_iops;
	inode->i_fop = &ecryptfs_main_fops;
	inode->i_mapping->a_ops = &ecryptfs_aops;
}