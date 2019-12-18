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
struct xdr_buf {int page_len; TYPE_2__* tail; int /*<<< orphan*/ ** pages; scalar_t__ page_base; TYPE_1__* head; } ;
struct rpcrdma_mr_seg {int mr_len; int /*<<< orphan*/ * mr_offset; int /*<<< orphan*/ * mr_page; } ;
typedef  enum rpcrdma_chunktype { ____Placeholder_rpcrdma_chunktype } rpcrdma_chunktype ;
struct TYPE_4__ {int iov_len; int /*<<< orphan*/ * iov_base; } ;
struct TYPE_3__ {int iov_len; int /*<<< orphan*/ * iov_base; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 void* min_t (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  u32 ; 
 scalar_t__ xprt_rdma_pad_optimize ; 

__attribute__((used)) static int
rpcrdma_convert_iovs(struct xdr_buf *xdrbuf, unsigned int pos,
	enum rpcrdma_chunktype type, struct rpcrdma_mr_seg *seg, int nsegs)
{
	int len, n = 0, p;

	if (pos == 0 && xdrbuf->head[0].iov_len) {
		seg[n].mr_page = NULL;
		seg[n].mr_offset = xdrbuf->head[0].iov_base;
		seg[n].mr_len = xdrbuf->head[0].iov_len;
		++n;
	}

	if (xdrbuf->page_len && (xdrbuf->pages[0] != NULL)) {
		if (n == nsegs)
			return 0;
		seg[n].mr_page = xdrbuf->pages[0];
		seg[n].mr_offset = (void *)(unsigned long) xdrbuf->page_base;
		seg[n].mr_len = min_t(u32,
			PAGE_SIZE - xdrbuf->page_base, xdrbuf->page_len);
		len = xdrbuf->page_len - seg[n].mr_len;
		++n;
		p = 1;
		while (len > 0) {
			if (n == nsegs)
				return 0;
			seg[n].mr_page = xdrbuf->pages[p];
			seg[n].mr_offset = NULL;
			seg[n].mr_len = min_t(u32, PAGE_SIZE, len);
			len -= seg[n].mr_len;
			++n;
			++p;
		}
	}

	if (xdrbuf->tail[0].iov_len) {
		/* the rpcrdma protocol allows us to omit any trailing
		 * xdr pad bytes, saving the server an RDMA operation. */
		if (xdrbuf->tail[0].iov_len < 4 && xprt_rdma_pad_optimize)
			return n;
		if (n == nsegs)
			return 0;
		seg[n].mr_page = NULL;
		seg[n].mr_offset = xdrbuf->tail[0].iov_base;
		seg[n].mr_len = xdrbuf->tail[0].iov_len;
		++n;
	}

	return n;
}