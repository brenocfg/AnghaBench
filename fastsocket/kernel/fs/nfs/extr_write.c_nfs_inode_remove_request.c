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
struct nfs_page {int /*<<< orphan*/  wb_flags; int /*<<< orphan*/  wb_page; TYPE_2__* wb_context; } ;
struct nfs_inode {int /*<<< orphan*/  npages; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ClearPagePrivate (int /*<<< orphan*/ ) ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_WBACK_BUSY (struct nfs_page*) ; 
 int /*<<< orphan*/  PG_MAPPED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_release_request (struct nfs_page*) ; 
 int /*<<< orphan*/  set_page_private (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_inode_remove_request(struct nfs_page *req)
{
	struct inode *inode = req->wb_context->dentry->d_inode;
	struct nfs_inode *nfsi = NFS_I(inode);

	BUG_ON (!NFS_WBACK_BUSY(req));

	spin_lock(&inode->i_lock);
	set_page_private(req->wb_page, 0);
	ClearPagePrivate(req->wb_page);
	clear_bit(PG_MAPPED, &req->wb_flags);
	nfsi->npages--;
	spin_unlock(&inode->i_lock);
	nfs_release_request(req);
}