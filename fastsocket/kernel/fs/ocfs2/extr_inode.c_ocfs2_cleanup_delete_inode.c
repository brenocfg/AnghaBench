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
struct TYPE_2__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,int) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_inode_now (struct inode*,int) ; 

__attribute__((used)) static void ocfs2_cleanup_delete_inode(struct inode *inode,
				       int sync_data)
{
	mlog(0, "Cleanup inode %llu, sync = %d\n",
	     (unsigned long long)OCFS2_I(inode)->ip_blkno, sync_data);
	if (sync_data)
		write_inode_now(inode, 1);
	truncate_inode_pages(&inode->i_data, 0);
}