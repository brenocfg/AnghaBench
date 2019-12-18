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
struct xdr_stream {unsigned int nwords; int /*<<< orphan*/ * page_ptr; int /*<<< orphan*/ * end; int /*<<< orphan*/ * p; struct kvec* iov; struct xdr_buf* buf; } ;
struct xdr_buf {unsigned int page_len; int buflen; int len; struct kvec* tail; struct kvec* head; } ;
struct kvec {int iov_len; scalar_t__ iov_base; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 void* XDR_QUADLEN (unsigned int) ; 
 int /*<<< orphan*/  xdr_shrink_bufhead (struct xdr_buf*,int) ; 
 int /*<<< orphan*/  xdr_shrink_pagelen (struct xdr_buf*,unsigned int) ; 

void xdr_read_pages(struct xdr_stream *xdr, unsigned int len)
{
	struct xdr_buf *buf = xdr->buf;
	struct kvec *iov;
	ssize_t shift;
	unsigned int nwords = XDR_QUADLEN(len);
	unsigned int end;
	int padding;

	if (xdr->nwords == 0)
		return;
	if (nwords > xdr->nwords) {
		nwords = xdr->nwords;
		len = nwords << 2;
	}
	/* Realign pages to current pointer position */
	iov  = buf->head;
	shift = iov->iov_len + (char *)iov->iov_base - (char *)xdr->p;
	if (shift > 0)
		xdr_shrink_bufhead(buf, shift);

	/* Truncate page data and move it into the tail */
	if (buf->page_len > len)
		xdr_shrink_pagelen(buf, buf->page_len - len);
	padding = (nwords << 2) - len;
	xdr->iov = iov = buf->tail;
	/* Compute remaining message length.  */
	end = iov->iov_len;
	shift = buf->buflen - buf->len;
	if (end > shift + padding)
		end -= shift;
	else
		end = padding;
	/*
	 * Position current pointer at beginning of tail, and
	 * set remaining message length.
	 */
	xdr->p = (__be32 *)((char *)iov->iov_base + padding);
	xdr->end = (__be32 *)((char *)iov->iov_base + end);
	xdr->page_ptr = NULL;
	xdr->nwords = XDR_QUADLEN(end - padding);
}