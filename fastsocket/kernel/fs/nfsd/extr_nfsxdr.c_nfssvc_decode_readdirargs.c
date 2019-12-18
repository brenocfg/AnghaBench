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
struct svc_rqst {int /*<<< orphan*/  rq_resused; int /*<<< orphan*/ * rq_respages; } ;
struct nfsd_readdirargs {scalar_t__ count; int /*<<< orphan*/  buffer; void* cookie; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/ * decode_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 
 int xdr_argsize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 

int
nfssvc_decode_readdirargs(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd_readdirargs *args)
{
	if (!(p = decode_fh(p, &args->fh)))
		return 0;
	args->cookie = ntohl(*p++);
	args->count  = ntohl(*p++);
	if (args->count > PAGE_SIZE)
		args->count = PAGE_SIZE;

	args->buffer = page_address(rqstp->rq_respages[rqstp->rq_resused++]);

	return xdr_argsize_check(rqstp, p);
}