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
typedef  int /*<<< orphan*/  u32 ;
struct xdr_buf {int /*<<< orphan*/  flags; int /*<<< orphan*/  head; int /*<<< orphan*/  len; } ;
struct rpc_rqst {struct xdr_buf rq_snd_buf; } ;
struct nfs_writeargs {int /*<<< orphan*/  pgbase; int /*<<< orphan*/  pages; int /*<<< orphan*/  fh; int /*<<< orphan*/  count; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  XDRBUF_WRITE ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_adjust_iovec (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_encode_fhandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_encode_pages (struct xdr_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_xdr_writeargs(struct rpc_rqst *req, __be32 *p, struct nfs_writeargs *args)
{
	struct xdr_buf *sndbuf = &req->rq_snd_buf;
	u32 offset = (u32)args->offset;
	u32 count = args->count;

	p = xdr_encode_fhandle(p, args->fh);
	*p++ = htonl(offset);
	*p++ = htonl(offset);
	*p++ = htonl(count);
	*p++ = htonl(count);
	sndbuf->len = xdr_adjust_iovec(sndbuf->head, p);

	/* Copy the page array */
	xdr_encode_pages(sndbuf, args->pages, args->pgbase, count);
	sndbuf->flags |= XDRBUF_WRITE;
	return 0;
}