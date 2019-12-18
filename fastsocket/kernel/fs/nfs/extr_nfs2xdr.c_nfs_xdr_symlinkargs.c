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
struct xdr_buf {size_t len; TYPE_1__* tail; TYPE_1__* head; } ;
struct rpc_rqst {struct xdr_buf rq_snd_buf; } ;
struct nfs_symlinkargs {int /*<<< orphan*/  sattr; int /*<<< orphan*/  pathlen; int /*<<< orphan*/  pages; int /*<<< orphan*/  fromlen; int /*<<< orphan*/  fromname; int /*<<< orphan*/  fromfh; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {size_t iov_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 size_t xdr_adjust_iovec (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_encode_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_fhandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_encode_pages (struct xdr_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_sattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_xdr_symlinkargs(struct rpc_rqst *req, __be32 *p, struct nfs_symlinkargs *args)
{
	struct xdr_buf *sndbuf = &req->rq_snd_buf;
	size_t pad;

	p = xdr_encode_fhandle(p, args->fromfh);
	p = xdr_encode_array(p, args->fromname, args->fromlen);
	*p++ = htonl(args->pathlen);
	sndbuf->len = xdr_adjust_iovec(sndbuf->head, p);

	xdr_encode_pages(sndbuf, args->pages, 0, args->pathlen);

	/*
	 * xdr_encode_pages may have added a few bytes to ensure the
	 * pathname ends on a 4-byte boundary.  Start encoding the
	 * attributes after the pad bytes.
	 */
	pad = sndbuf->tail->iov_len;
	if (pad > 0)
		p++;
	p = xdr_encode_sattr(p, args->sattr);
	sndbuf->len += xdr_adjust_iovec(sndbuf->tail, p) - pad;
	return 0;
}