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
struct xdr_buf {unsigned int page_base; unsigned int page_len; unsigned int buflen; struct page** pages; struct kvec* tail; struct kvec* head; } ;
struct page {int dummy; } ;
struct kvec {char* iov_base; unsigned int iov_len; } ;

/* Variables and functions */

void
xdr_inline_pages(struct xdr_buf *xdr, unsigned int offset,
		 struct page **pages, unsigned int base, unsigned int len)
{
	struct kvec *head = xdr->head;
	struct kvec *tail = xdr->tail;
	char *buf = (char *)head->iov_base;
	unsigned int buflen = head->iov_len;

	head->iov_len  = offset;

	xdr->pages = pages;
	xdr->page_base = base;
	xdr->page_len = len;

	tail->iov_base = buf + offset;
	tail->iov_len = buflen - offset;

	xdr->buflen += len;
}