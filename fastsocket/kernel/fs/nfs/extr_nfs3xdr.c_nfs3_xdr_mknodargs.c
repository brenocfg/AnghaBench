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
struct nfs3_mknodargs {scalar_t__ type; int /*<<< orphan*/  rdev; int /*<<< orphan*/  sattr; int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ MAJOR (int /*<<< orphan*/ ) ; 
 scalar_t__ MINOR (int /*<<< orphan*/ ) ; 
 scalar_t__ NF3BLK ; 
 scalar_t__ NF3CHR ; 
 void* htonl (scalar_t__) ; 
 int /*<<< orphan*/  xdr_adjust_iovec (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_encode_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_fhandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_sattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs3_xdr_mknodargs(struct rpc_rqst *req, __be32 *p, struct nfs3_mknodargs *args)
{
	p = xdr_encode_fhandle(p, args->fh);
	p = xdr_encode_array(p, args->name, args->len);
	*p++ = htonl(args->type);
	p = xdr_encode_sattr(p, args->sattr);
	if (args->type == NF3CHR || args->type == NF3BLK) {
		*p++ = htonl(MAJOR(args->rdev));
		*p++ = htonl(MINOR(args->rdev));
	}

	req->rq_slen = xdr_adjust_iovec(req->rq_svec, p);
	return 0;
}