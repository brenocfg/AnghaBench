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
typedef  int u32 ;
struct svc_rqst {int /*<<< orphan*/ * rq_respages; int /*<<< orphan*/  rq_resused; } ;
struct nfsd3_readdirargs {int count; int /*<<< orphan*/  buffer; void* dircount; int /*<<< orphan*/ * verf; int /*<<< orphan*/  cookie; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/ * decode_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 
 int svc_max_payload (struct svc_rqst*) ; 
 int xdr_argsize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_decode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
nfs3svc_decode_readdirplusargs(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd3_readdirargs *args)
{
	int len, pn;
	u32 max_blocksize = svc_max_payload(rqstp);

	if (!(p = decode_fh(p, &args->fh)))
		return 0;
	p = xdr_decode_hyper(p, &args->cookie);
	args->verf     = p; p += 2;
	args->dircount = ntohl(*p++);
	args->count    = ntohl(*p++);

	len = (args->count > max_blocksize) ? max_blocksize :
						  args->count;
	args->count = len;

	while (len > 0) {
		pn = rqstp->rq_resused++;
		if (!args->buffer)
			args->buffer = page_address(rqstp->rq_respages[pn]);
		len -= PAGE_SIZE;
	}

	return xdr_argsize_check(rqstp, p);
}