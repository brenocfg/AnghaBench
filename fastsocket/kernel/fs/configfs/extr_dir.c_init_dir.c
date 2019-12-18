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
struct inode {int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  configfs_dir_inode_operations ; 
 int /*<<< orphan*/  configfs_dir_operations ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 

__attribute__((used)) static int init_dir(struct inode * inode)
{
	inode->i_op = &configfs_dir_inode_operations;
	inode->i_fop = &configfs_dir_operations;

	/* directory inodes start off with i_nlink == 2 (for "." entry) */
	inc_nlink(inode);
	return 0;
}