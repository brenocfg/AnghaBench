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
struct xdr_stream {TYPE_1__* buf; int /*<<< orphan*/  nwords; } ;
struct TYPE_2__ {int /*<<< orphan*/  page_len; } ;

/* Variables and functions */
 scalar_t__ XDR_QUADLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_read_pages (struct xdr_stream*,unsigned int) ; 
 int /*<<< orphan*/  xdr_set_page_base (struct xdr_stream*,int /*<<< orphan*/ ,unsigned int) ; 

void xdr_enter_page(struct xdr_stream *xdr, unsigned int len)
{
	xdr_read_pages(xdr, len);
	/*
	 * Position current pointer at beginning of tail, and
	 * set remaining message length.
	 */
	xdr_set_page_base(xdr, 0, len);
	xdr->nwords += XDR_QUADLEN(xdr->buf->page_len);
}