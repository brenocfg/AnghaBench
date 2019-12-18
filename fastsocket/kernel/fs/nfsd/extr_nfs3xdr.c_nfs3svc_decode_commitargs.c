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
struct svc_rqst {int dummy; } ;
struct nfsd3_commitargs {int /*<<< orphan*/  count; int /*<<< orphan*/  offset; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/ * decode_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int xdr_argsize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_decode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
nfs3svc_decode_commitargs(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd3_commitargs *args)
{
	if (!(p = decode_fh(p, &args->fh)))
		return 0;
	p = xdr_decode_hyper(p, &args->offset);
	args->count = ntohl(*p++);

	return xdr_argsize_check(rqstp, p);
}