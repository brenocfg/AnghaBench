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
typedef  int u32 ;
struct rpc_rqst {int /*<<< orphan*/  rq_rcv_buf; int /*<<< orphan*/  rq_svec; int /*<<< orphan*/  rq_slen; TYPE_1__* rq_cred; } ;
struct rpc_auth {int au_rslack; } ;
struct nfs3_readdirargs {int count; int /*<<< orphan*/  pages; scalar_t__ plus; int /*<<< orphan*/ * verf; int /*<<< orphan*/  cookie; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {struct rpc_auth* cr_auth; } ;

/* Variables and functions */
 int NFS3_readdirres_sz ; 
 int RPC_REPHDRSIZE ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  xdr_adjust_iovec (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_encode_fhandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_inline_pages (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nfs3_xdr_readdirargs(struct rpc_rqst *req, __be32 *p, struct nfs3_readdirargs *args)
{
	struct rpc_auth	*auth = req->rq_cred->cr_auth;
	unsigned int replen;
	u32 count = args->count;

	p = xdr_encode_fhandle(p, args->fh);
	p = xdr_encode_hyper(p, args->cookie);
	*p++ = args->verf[0];
	*p++ = args->verf[1];
	if (args->plus) {
		/* readdirplus: need dircount + buffer size.
		 * We just make sure we make dircount big enough */
		*p++ = htonl(count >> 3);
	}
	*p++ = htonl(count);
	req->rq_slen = xdr_adjust_iovec(req->rq_svec, p);

	/* Inline the page array */
	replen = (RPC_REPHDRSIZE + auth->au_rslack + NFS3_readdirres_sz) << 2;
	xdr_inline_pages(&req->rq_rcv_buf, replen, args->pages, 0, count);
	return 0;
}