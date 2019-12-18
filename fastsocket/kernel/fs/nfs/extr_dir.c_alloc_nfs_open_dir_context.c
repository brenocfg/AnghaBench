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
struct rpc_cred {int dummy; } ;
struct nfs_open_dir_context {int /*<<< orphan*/  cred; scalar_t__ dup_cookie; scalar_t__ dir_cookie; int /*<<< orphan*/  attr_gencount; scalar_t__ duped; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  attr_gencount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct nfs_open_dir_context* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  get_rpccred (struct rpc_cred*) ; 
 struct nfs_open_dir_context* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfs_open_dir_context *alloc_nfs_open_dir_context(struct inode *dir, struct rpc_cred *cred)
{
	struct nfs_open_dir_context *ctx;
	ctx = kmalloc(sizeof(*ctx), GFP_KERNEL);
	if (ctx != NULL) {
		ctx->duped = 0;
		ctx->attr_gencount = NFS_I(dir)->attr_gencount;
		ctx->dir_cookie = 0;
		ctx->dup_cookie = 0;
		ctx->cred = get_rpccred(cred);
		return ctx;
	}
	return  ERR_PTR(-ENOMEM);
}