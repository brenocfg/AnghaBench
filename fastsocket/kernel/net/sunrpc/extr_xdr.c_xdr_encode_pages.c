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
typedef  char u32 ;
struct xdr_buf {unsigned int page_base; unsigned int page_len; unsigned int buflen; unsigned int len; TYPE_1__* head; struct page** pages; struct kvec* tail; } ;
struct page {int dummy; } ;
struct kvec {char* iov_base; unsigned int iov_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  iov_len; scalar_t__ iov_base; } ;

/* Variables and functions */
 int XDR_QUADLEN (int /*<<< orphan*/ ) ; 

void
xdr_encode_pages(struct xdr_buf *xdr, struct page **pages, unsigned int base,
		 unsigned int len)
{
	struct kvec *tail = xdr->tail;
	u32 *p;

	xdr->pages = pages;
	xdr->page_base = base;
	xdr->page_len = len;

	p = (u32 *)xdr->head[0].iov_base + XDR_QUADLEN(xdr->head[0].iov_len);
	tail->iov_base = p;
	tail->iov_len = 0;

	if (len & 3) {
		unsigned int pad = 4 - (len & 3);

		*p = 0;
		tail->iov_base = (char *)p + (len & 3);
		tail->iov_len  = pad;
		len += pad;
	}
	xdr->buflen += len;
	xdr->len += len;
}