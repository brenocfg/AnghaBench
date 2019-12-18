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
struct smb_rqst {int rq_npages; int /*<<< orphan*/  rq_pagesz; int /*<<< orphan*/  rq_tailsz; int /*<<< orphan*/ * rq_pages; } ;
struct kvec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmap (int /*<<< orphan*/ ) ; 

void
cifs_rqst_page_to_kvec(struct smb_rqst *rqst, unsigned int idx,
			struct kvec *iov)
{
	/*
	 * FIXME: We could avoid this kmap altogether if we used
	 * kernel_sendpage instead of kernel_sendmsg. That will only
	 * work if signing is disabled though as sendpage inlines the
	 * page directly into the fraglist. If userspace modifies the
	 * page after we calculate the signature, then the server will
	 * reject it and may break the connection. kernel_sendmsg does
	 * an extra copy of the data and avoids that issue.
	 */
	iov->iov_base = kmap(rqst->rq_pages[idx]);

	/* if last page, don't send beyond this offset into page */
	if (idx == (rqst->rq_npages - 1))
		iov->iov_len = rqst->rq_tailsz;
	else
		iov->iov_len = rqst->rq_pagesz;
}