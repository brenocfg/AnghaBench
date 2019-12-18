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
struct smb_rqst {unsigned int rq_nvec; int rq_npages; int rq_pagesz; scalar_t__ rq_tailsz; struct kvec* rq_iov; } ;
struct kvec {scalar_t__ iov_len; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long
rqst_len(struct smb_rqst *rqst)
{
	unsigned int i;
	struct kvec *iov = rqst->rq_iov;
	unsigned long buflen = 0;

	/* total up iov array first */
	for (i = 0; i < rqst->rq_nvec; i++)
		buflen += iov[i].iov_len;

	/* add in the page array if there is one */
	if (rqst->rq_npages) {
		buflen += rqst->rq_pagesz * (rqst->rq_npages - 1);
		buflen += rqst->rq_tailsz;
	}

	return buflen;
}