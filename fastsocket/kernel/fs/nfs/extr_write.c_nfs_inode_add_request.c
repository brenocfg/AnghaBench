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
struct nfs_page {int /*<<< orphan*/  wb_kref; int /*<<< orphan*/  wb_page; int /*<<< orphan*/  wb_flags; } ;
struct nfs_inode {int /*<<< orphan*/  npages; int /*<<< orphan*/  change_attr; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_WRITE ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  PG_MAPPED ; 
 int /*<<< orphan*/  SetPagePrivate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 scalar_t__ nfs_have_delegation (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_lock_request (struct nfs_page*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_private (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_inode_add_request(struct inode *inode, struct nfs_page *req)
{
	struct nfs_inode *nfsi = NFS_I(inode);

	/* Lock the request! */
	nfs_lock_request(req);

	spin_lock(&inode->i_lock);
	if (!nfsi->npages && nfs_have_delegation(inode, FMODE_WRITE))
		nfsi->change_attr++;
	set_bit(PG_MAPPED, &req->wb_flags);
	SetPagePrivate(req->wb_page);
	set_page_private(req->wb_page, (unsigned long)req);
	nfsi->npages++;
	kref_get(&req->wb_kref);
	spin_unlock(&inode->i_lock);
}