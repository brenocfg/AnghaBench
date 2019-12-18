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
struct rpc_rqst {int /*<<< orphan*/  rq_svec; int /*<<< orphan*/  rq_slen; } ;
struct nfs3_sattrargs {int /*<<< orphan*/  guardtime; scalar_t__ guard; int /*<<< orphan*/  sattr; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 int /*<<< orphan*/  xdr_adjust_iovec (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_encode_fhandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_sattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_time3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfs3_xdr_sattrargs(struct rpc_rqst *req, __be32 *p, struct nfs3_sattrargs *args)
{
	p = xdr_encode_fhandle(p, args->fh);
	p = xdr_encode_sattr(p, args->sattr);
	*p++ = htonl(args->guard);
	if (args->guard)
		p = xdr_encode_time3(p, &args->guardtime);
	req->rq_slen = xdr_adjust_iovec(req->rq_svec, p);
	return 0;
}