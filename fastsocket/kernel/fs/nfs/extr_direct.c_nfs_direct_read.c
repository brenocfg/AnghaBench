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
struct nfs_lock_context {int dummy; } ;
struct nfs_direct_req {struct kiocb* iocb; struct nfs_lock_context* l_ctx; int /*<<< orphan*/  ctx; struct inode* inode; } ;
struct kiocb {TYPE_2__* ki_filp; } ;
struct iovec {int dummy; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {TYPE_1__* f_mapping; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 scalar_t__ IS_ERR (struct nfs_lock_context*) ; 
 scalar_t__ PTR_ERR (struct nfs_lock_context*) ; 
 int /*<<< orphan*/  get_nfs_open_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_sync_kiocb (struct kiocb*) ; 
 scalar_t__ nfs_direct_read_schedule_iovec (struct nfs_direct_req*,struct iovec const*,unsigned long,int /*<<< orphan*/ ) ; 
 struct nfs_direct_req* nfs_direct_req_alloc () ; 
 int /*<<< orphan*/  nfs_direct_req_release (struct nfs_direct_req*) ; 
 scalar_t__ nfs_direct_wait (struct nfs_direct_req*) ; 
 int /*<<< orphan*/  nfs_file_open_context (TYPE_2__*) ; 
 struct nfs_lock_context* nfs_get_lock_context (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t nfs_direct_read(struct kiocb *iocb, const struct iovec *iov,
			       unsigned long nr_segs, loff_t pos)
{
	ssize_t result = -ENOMEM;
	struct inode *inode = iocb->ki_filp->f_mapping->host;
	struct nfs_direct_req *dreq;
	struct nfs_lock_context *l_ctx;

	dreq = nfs_direct_req_alloc();
	if (dreq == NULL)
		goto out;

	dreq->inode = inode;
	dreq->ctx = get_nfs_open_context(nfs_file_open_context(iocb->ki_filp));
	l_ctx = nfs_get_lock_context(dreq->ctx);
	if (IS_ERR(l_ctx)) {
		result = PTR_ERR(l_ctx);
		goto out_release;
	}
	dreq->l_ctx = l_ctx;
	if (!is_sync_kiocb(iocb))
		dreq->iocb = iocb;

	result = nfs_direct_read_schedule_iovec(dreq, iov, nr_segs, pos);
	if (!result)
		result = nfs_direct_wait(dreq);
out_release:
	nfs_direct_req_release(dreq);
out:
	return result;
}