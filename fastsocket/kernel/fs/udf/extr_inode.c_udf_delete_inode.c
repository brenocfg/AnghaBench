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
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_SYNC (struct inode*) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_free_inode (struct inode*) ; 
 int /*<<< orphan*/  udf_truncate (struct inode*) ; 
 int /*<<< orphan*/  udf_update_inode (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

void udf_delete_inode(struct inode *inode)
{
	truncate_inode_pages(&inode->i_data, 0);

	if (is_bad_inode(inode))
		goto no_delete;

	inode->i_size = 0;
	udf_truncate(inode);
	lock_kernel();

	udf_update_inode(inode, IS_SYNC(inode));
	udf_free_inode(inode);

	unlock_kernel();
	return;

no_delete:
	clear_inode(inode);
}