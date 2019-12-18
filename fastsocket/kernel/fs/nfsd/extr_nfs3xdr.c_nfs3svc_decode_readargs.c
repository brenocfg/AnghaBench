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
typedef  unsigned int u32 ;
struct svc_rqst {TYPE_1__* rq_vec; int /*<<< orphan*/ * rq_respages; int /*<<< orphan*/  rq_resused; } ;
struct nfsd3_readargs {unsigned int count; int vlen; int /*<<< orphan*/  offset; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {unsigned int iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/ * decode_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 
 unsigned int svc_max_payload (struct svc_rqst*) ; 
 int xdr_argsize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_decode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
nfs3svc_decode_readargs(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd3_readargs *args)
{
	unsigned int len;
	int v,pn;
	u32 max_blocksize = svc_max_payload(rqstp);

	if (!(p = decode_fh(p, &args->fh)))
		return 0;
	p = xdr_decode_hyper(p, &args->offset);

	len = args->count = ntohl(*p++);

	if (len > max_blocksize)
		len = max_blocksize;

	/* set up the kvec */
	v=0;
	while (len > 0) {
		pn = rqstp->rq_resused++;
		rqstp->rq_vec[v].iov_base = page_address(rqstp->rq_respages[pn]);
		rqstp->rq_vec[v].iov_len = len < PAGE_SIZE? len : PAGE_SIZE;
		len -= rqstp->rq_vec[v].iov_len;
		v++;
	}
	args->vlen = v;
	return xdr_argsize_check(rqstp, p);
}