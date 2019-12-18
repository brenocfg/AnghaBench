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
struct rpc_rqst {int /*<<< orphan*/  rq_rcv_buf; int /*<<< orphan*/  rq_svec; int /*<<< orphan*/  rq_slen; TYPE_1__* rq_cred; } ;
struct rpc_auth {int au_rslack; } ;
struct nfs_readlinkargs {int /*<<< orphan*/  pglen; int /*<<< orphan*/  pgbase; int /*<<< orphan*/  pages; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {struct rpc_auth* cr_auth; } ;

/* Variables and functions */
 int NFS_readlinkres_sz ; 
 int RPC_REPHDRSIZE ; 
 int /*<<< orphan*/  xdr_adjust_iovec (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_encode_fhandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_inline_pages (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_xdr_readlinkargs(struct rpc_rqst *req, __be32 *p, struct nfs_readlinkargs *args)
{
	struct rpc_auth	*auth = req->rq_cred->cr_auth;
	unsigned int replen;

	p = xdr_encode_fhandle(p, args->fh);
	req->rq_slen = xdr_adjust_iovec(req->rq_svec, p);

	/* Inline the page array */
	replen = (RPC_REPHDRSIZE + auth->au_rslack + NFS_readlinkres_sz) << 2;
	xdr_inline_pages(&req->rq_rcv_buf, replen, args->pages, args->pgbase, args->pglen);
	return 0;
}