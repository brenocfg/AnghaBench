#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int page_len; TYPE_1__* head; } ;
struct svc_rqst {TYPE_3__* rq_vec; int /*<<< orphan*/ * rq_pages; TYPE_2__ rq_arg; } ;
struct nfsd_writeargs {unsigned int len; int vlen; void* offset; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {unsigned int iov_len; void* iov_base; } ;
struct TYPE_4__ {void* iov_base; unsigned int iov_len; } ;

/* Variables and functions */
 unsigned int NFSSVC_MAXBLKSIZE_V2 ; 
 unsigned int PAGE_SIZE ; 
 int XDR_QUADLEN (unsigned int) ; 
 int /*<<< orphan*/ * decode_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 void* page_address (int /*<<< orphan*/ ) ; 

int
nfssvc_decode_writeargs(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd_writeargs *args)
{
	unsigned int len, hdr, dlen;
	int v;

	if (!(p = decode_fh(p, &args->fh)))
		return 0;

	p++;				/* beginoffset */
	args->offset = ntohl(*p++);	/* offset */
	p++;				/* totalcount */
	len = args->len = ntohl(*p++);
	/*
	 * The protocol specifies a maximum of 8192 bytes.
	 */
	if (len > NFSSVC_MAXBLKSIZE_V2)
		return 0;

	/*
	 * Check to make sure that we got the right number of
	 * bytes.
	 */
	hdr = (void*)p - rqstp->rq_arg.head[0].iov_base;
	dlen = rqstp->rq_arg.head[0].iov_len + rqstp->rq_arg.page_len
		- hdr;

	/*
	 * Round the length of the data which was specified up to
	 * the next multiple of XDR units and then compare that
	 * against the length which was actually received.
	 * Note that when RPCSEC/GSS (for example) is used, the
	 * data buffer can be padded so dlen might be larger
	 * than required.  It must never be smaller.
	 */
	if (dlen < XDR_QUADLEN(len)*4)
		return 0;

	rqstp->rq_vec[0].iov_base = (void*)p;
	rqstp->rq_vec[0].iov_len = rqstp->rq_arg.head[0].iov_len - hdr;
	v = 0;
	while (len > rqstp->rq_vec[v].iov_len) {
		len -= rqstp->rq_vec[v].iov_len;
		v++;
		rqstp->rq_vec[v].iov_base = page_address(rqstp->rq_pages[v]);
		rqstp->rq_vec[v].iov_len = PAGE_SIZE;
	}
	rqstp->rq_vec[v].iov_len = len;
	args->vlen = v + 1;
	return 1;
}