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
struct xdr_stream {int /*<<< orphan*/ * p; int /*<<< orphan*/ * end; struct kvec* iov; struct xdr_buf* buf; } ;
struct xdr_buf {int buflen; int page_len; size_t len; TYPE_1__* tail; struct kvec* head; } ;
struct kvec {int iov_len; scalar_t__ iov_base; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int iov_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

void xdr_init_encode(struct xdr_stream *xdr, struct xdr_buf *buf, __be32 *p)
{
	struct kvec *iov = buf->head;
	int scratch_len = buf->buflen - buf->page_len - buf->tail[0].iov_len;

	BUG_ON(scratch_len < 0);
	xdr->buf = buf;
	xdr->iov = iov;
	xdr->p = (__be32 *)((char *)iov->iov_base + iov->iov_len);
	xdr->end = (__be32 *)((char *)iov->iov_base + scratch_len);
	BUG_ON(iov->iov_len > scratch_len);

	if (p != xdr->p && p != NULL) {
		size_t len;

		BUG_ON(p < xdr->p || p > xdr->end);
		len = (char *)p - (char *)xdr->p;
		xdr->p = p;
		buf->len += len;
		iov->iov_len += len;
	}
}