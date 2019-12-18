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
struct rpc_rqst {int /*<<< orphan*/  rq_snd_buf; int /*<<< orphan*/  rq_svec; int /*<<< orphan*/  rq_slen; } ;
struct nfs3_symlinkargs {int /*<<< orphan*/  pathlen; int /*<<< orphan*/  pages; int /*<<< orphan*/  sattr; int /*<<< orphan*/  fromlen; int /*<<< orphan*/  fromname; int /*<<< orphan*/  fromfh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_adjust_iovec (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_encode_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_fhandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_encode_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_sattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs3_xdr_symlinkargs(struct rpc_rqst *req, __be32 *p, struct nfs3_symlinkargs *args)
{
	p = xdr_encode_fhandle(p, args->fromfh);
	p = xdr_encode_array(p, args->fromname, args->fromlen);
	p = xdr_encode_sattr(p, args->sattr);
	*p++ = htonl(args->pathlen);
	req->rq_slen = xdr_adjust_iovec(req->rq_svec, p);

	/* Copy the page */
	xdr_encode_pages(&req->rq_snd_buf, args->pages, 0, args->pathlen);
	return 0;
}