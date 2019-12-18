#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
struct nfs_open_context {TYPE_2__* dentry; int /*<<< orphan*/ * cred; TYPE_1__ lock_context; int /*<<< orphan*/  list; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* close_context ) (struct nfs_open_context*,int) ;} ;
struct TYPE_5__ {struct super_block* d_sb; struct inode* d_inode; } ;

/* Variables and functions */
 TYPE_3__* NFS_PROTO (struct inode*) ; 
 int /*<<< orphan*/  atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dput (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct nfs_open_context*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_sb_deactive (struct super_block*) ; 
 int /*<<< orphan*/  nfs_sb_deactive_async (struct super_block*) ; 
 int /*<<< orphan*/  put_rpccred (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nfs_open_context*,int) ; 

__attribute__((used)) static void __put_nfs_open_context(struct nfs_open_context *ctx, int is_sync)
{
	struct inode *inode = ctx->dentry->d_inode;
	struct super_block *sb = ctx->dentry->d_sb;

	if (!list_empty(&ctx->list)) {
		if (!atomic_dec_and_lock(&ctx->lock_context.count, &inode->i_lock))
			return;
		list_del(&ctx->list);
		spin_unlock(&inode->i_lock);
	} else if (!atomic_dec_and_test(&ctx->lock_context.count))
		return;
	if (inode != NULL)
		NFS_PROTO(inode)->close_context(ctx, is_sync);
	if (ctx->cred != NULL)
		put_rpccred(ctx->cred);
	dput(ctx->dentry);
	if (is_sync)
		nfs_sb_deactive(sb);
	else
		nfs_sb_deactive_async(sb);
	kfree(ctx);
}