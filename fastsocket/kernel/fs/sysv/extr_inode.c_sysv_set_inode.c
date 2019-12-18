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
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_size; int /*<<< orphan*/ * i_op; TYPE_1__* i_mapping; scalar_t__ i_blocks; int /*<<< orphan*/ * i_fop; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 TYPE_2__* SYSV_I (struct inode*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd_terminate_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sysv_aops ; 
 int /*<<< orphan*/  sysv_dir_inode_operations ; 
 int /*<<< orphan*/  sysv_dir_operations ; 
 int /*<<< orphan*/  sysv_fast_symlink_inode_operations ; 
 int /*<<< orphan*/  sysv_file_inode_operations ; 
 int /*<<< orphan*/  sysv_file_operations ; 
 int /*<<< orphan*/  sysv_symlink_inode_operations ; 

void sysv_set_inode(struct inode *inode, dev_t rdev)
{
	if (S_ISREG(inode->i_mode)) {
		inode->i_op = &sysv_file_inode_operations;
		inode->i_fop = &sysv_file_operations;
		inode->i_mapping->a_ops = &sysv_aops;
	} else if (S_ISDIR(inode->i_mode)) {
		inode->i_op = &sysv_dir_inode_operations;
		inode->i_fop = &sysv_dir_operations;
		inode->i_mapping->a_ops = &sysv_aops;
	} else if (S_ISLNK(inode->i_mode)) {
		if (inode->i_blocks) {
			inode->i_op = &sysv_symlink_inode_operations;
			inode->i_mapping->a_ops = &sysv_aops;
		} else {
			inode->i_op = &sysv_fast_symlink_inode_operations;
			nd_terminate_link(SYSV_I(inode)->i_data, inode->i_size,
				sizeof(SYSV_I(inode)->i_data) - 1);
		}
	} else
		init_special_inode(inode, inode->i_mode, rdev);
}