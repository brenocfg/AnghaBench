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
struct inode {int /*<<< orphan*/  i_data; } ;
struct TYPE_2__ {scalar_t__ fileset; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_Freewmap ; 
 scalar_t__ FILESYSTEM_I ; 
 TYPE_1__* JFS_IP (struct inode*) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  diFree (struct inode*) ; 
 int /*<<< orphan*/  is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  jfs_free_zero_link (struct inode*) ; 
 int /*<<< orphan*/  jfs_info (char*,struct inode*) ; 
 scalar_t__ test_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_dq_drop (struct inode*) ; 
 int /*<<< orphan*/  vfs_dq_free_inode (struct inode*) ; 
 int /*<<< orphan*/  vfs_dq_init (struct inode*) ; 

void jfs_delete_inode(struct inode *inode)
{
	jfs_info("In jfs_delete_inode, inode = 0x%p", inode);

	if (!is_bad_inode(inode) &&
	    (JFS_IP(inode)->fileset == FILESYSTEM_I)) {
		truncate_inode_pages(&inode->i_data, 0);

		if (test_cflag(COMMIT_Freewmap, inode))
			jfs_free_zero_link(inode);

		diFree(inode);

		/*
		 * Free the inode from the quota allocation.
		 */
		vfs_dq_init(inode);
		vfs_dq_free_inode(inode);
		vfs_dq_drop(inode);
	}

	clear_inode(inode);
}