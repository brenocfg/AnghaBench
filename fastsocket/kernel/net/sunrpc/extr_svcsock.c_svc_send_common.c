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
struct xdr_buf {size_t page_base; unsigned int page_len; int len; TYPE_2__* tail; TYPE_1__* head; struct page** pages; } ;
struct socket {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_4__ {int iov_len; } ;
struct TYPE_3__ {int iov_len; } ;

/* Variables and functions */
 unsigned int MSG_MORE ; 
 size_t PAGE_SIZE ; 
 int kernel_sendpage (struct socket*,struct page*,unsigned long,int,unsigned int) ; 

int svc_send_common(struct socket *sock, struct xdr_buf *xdr,
		    struct page *headpage, unsigned long headoffset,
		    struct page *tailpage, unsigned long tailoffset)
{
	int		result;
	int		size;
	struct page	**ppage = xdr->pages;
	size_t		base = xdr->page_base;
	unsigned int	pglen = xdr->page_len;
	unsigned int	flags = MSG_MORE;
	int		slen;
	int		len = 0;

	slen = xdr->len;

	/* send head */
	if (slen == xdr->head[0].iov_len)
		flags = 0;
	len = kernel_sendpage(sock, headpage, headoffset,
				  xdr->head[0].iov_len, flags);
	if (len != xdr->head[0].iov_len)
		goto out;
	slen -= xdr->head[0].iov_len;
	if (slen == 0)
		goto out;

	/* send page data */
	size = PAGE_SIZE - base < pglen ? PAGE_SIZE - base : pglen;
	while (pglen > 0) {
		if (slen == size)
			flags = 0;
		result = kernel_sendpage(sock, *ppage, base, size, flags);
		if (result > 0)
			len += result;
		if (result != size)
			goto out;
		slen -= size;
		pglen -= size;
		size = PAGE_SIZE < pglen ? PAGE_SIZE : pglen;
		base = 0;
		ppage++;
	}

	/* send tail */
	if (xdr->tail[0].iov_len) {
		result = kernel_sendpage(sock, tailpage, tailoffset,
				   xdr->tail[0].iov_len, 0);
		if (result > 0)
			len += result;
	}

out:
	return len;
}