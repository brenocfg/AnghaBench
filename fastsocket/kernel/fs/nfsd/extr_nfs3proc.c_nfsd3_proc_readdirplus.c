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
typedef  int /*<<< orphan*/  u32 ;
struct svc_rqst {int rq_resused; int /*<<< orphan*/ * rq_respages; } ;
struct TYPE_2__ {int /*<<< orphan*/  err; } ;
struct nfsd3_readdirres {int count; int buflen; void** offset; void** offset1; scalar_t__ buffer; int /*<<< orphan*/  verf; TYPE_1__ common; int /*<<< orphan*/  fh; struct svc_rqst* rqstp; } ;
struct nfsd3_readdirargs {int count; int cookie; int /*<<< orphan*/  verf; scalar_t__ buffer; int /*<<< orphan*/  fh; } ;
typedef  int loff_t ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  RETURN_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs3svc_encode_entry_plus ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfsd_readdir (struct svc_rqst*,int /*<<< orphan*/ *,int*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (void**) ; 
 int /*<<< orphan*/  xdr_encode_hyper (void**,int) ; 

__attribute__((used)) static __be32
nfsd3_proc_readdirplus(struct svc_rqst *rqstp, struct nfsd3_readdirargs *argp,
					       struct nfsd3_readdirres  *resp)
{
	__be32	nfserr;
	int	count = 0;
	loff_t	offset;
	int	i;
	caddr_t	page_addr = NULL;

	dprintk("nfsd: READDIR+(3) %s %d bytes at %d\n",
				SVCFH_fmt(&argp->fh),
				argp->count, (u32) argp->cookie);

	/* Convert byte count to number of words (i.e. >> 2),
	 * and reserve room for the NULL ptr & eof flag (-2 words) */
	resp->count = (argp->count >> 2) - 2;

	/* Read directory and encode entries on the fly */
	fh_copy(&resp->fh, &argp->fh);

	resp->common.err = nfs_ok;
	resp->buffer = argp->buffer;
	resp->buflen = resp->count;
	resp->rqstp = rqstp;
	offset = argp->cookie;
	nfserr = nfsd_readdir(rqstp, &resp->fh,
				     &offset,
				     &resp->common,
				     nfs3svc_encode_entry_plus);
	memcpy(resp->verf, argp->verf, 8);
	for (i=1; i<rqstp->rq_resused ; i++) {
		page_addr = page_address(rqstp->rq_respages[i]);

		if (((caddr_t)resp->buffer >= page_addr) &&
		    ((caddr_t)resp->buffer < page_addr + PAGE_SIZE)) {
			count += (caddr_t)resp->buffer - page_addr;
			break;
		}
		count += PAGE_SIZE;
	}
	resp->count = count >> 2;
	if (resp->offset) {
		if (unlikely(resp->offset1)) {
			/* we ended up with offset on a page boundary */
			*resp->offset = htonl(offset >> 32);
			*resp->offset1 = htonl(offset & 0xffffffff);
			resp->offset1 = NULL;
		} else {
			xdr_encode_hyper(resp->offset, offset);
		}
	}

	RETURN_STATUS(nfserr);
}