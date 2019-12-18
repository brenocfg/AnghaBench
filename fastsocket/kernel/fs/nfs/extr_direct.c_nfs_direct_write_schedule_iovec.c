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
struct nfs_pageio_descriptor {struct nfs_direct_req* pg_dreq; } ;
struct nfs_direct_req {struct inode* inode; } ;
struct iovec {size_t iov_len; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  size_t loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_pageio_init ) (struct nfs_pageio_descriptor*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ EIO ; 
 int /*<<< orphan*/  FLUSH_COND_STABLE ; 
 TYPE_1__* NFS_PROTO (struct inode*) ; 
 int /*<<< orphan*/  get_dreq (struct nfs_direct_req*) ; 
 int /*<<< orphan*/  nfs_direct_req_release (struct nfs_direct_req*) ; 
 int /*<<< orphan*/  nfs_direct_write_complete (struct nfs_direct_req*,struct inode*) ; 
 int /*<<< orphan*/  nfs_direct_write_completion_ops ; 
 scalar_t__ nfs_direct_write_schedule_segment (struct nfs_pageio_descriptor*,struct iovec const*,size_t) ; 
 int /*<<< orphan*/  nfs_pageio_complete (struct nfs_pageio_descriptor*) ; 
 scalar_t__ put_dreq (struct nfs_direct_req*) ; 
 int /*<<< orphan*/  stub1 (struct nfs_pageio_descriptor*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t nfs_direct_write_schedule_iovec(struct nfs_direct_req *dreq,
					       const struct iovec *iov,
					       unsigned long nr_segs,
					       loff_t pos)
{
	struct nfs_pageio_descriptor desc;
	struct inode *inode = dreq->inode;
	ssize_t result = 0;
	size_t requested_bytes = 0;
	unsigned long seg;

	NFS_PROTO(inode)->write_pageio_init(&desc, inode, FLUSH_COND_STABLE,
			      &nfs_direct_write_completion_ops);
	desc.pg_dreq = dreq;
	get_dreq(dreq);

	for (seg = 0; seg < nr_segs; seg++) {
		const struct iovec *vec = &iov[seg];
		result = nfs_direct_write_schedule_segment(&desc, vec, pos);
		if (result < 0)
			break;
		requested_bytes += result;
		if ((size_t)result < vec->iov_len)
			break;
		pos += vec->iov_len;
	}
	nfs_pageio_complete(&desc);

	/*
	 * If no bytes were started, return the error, and let the
	 * generic layer handle the completion.
	 */
	if (requested_bytes == 0) {
		nfs_direct_req_release(dreq);
		return result < 0 ? result : -EIO;
	}

	if (put_dreq(dreq))
		nfs_direct_write_complete(dreq, dreq->inode);
	return 0;
}