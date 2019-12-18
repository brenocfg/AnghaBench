#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct svc_rqst {int /*<<< orphan*/  rq_vec; } ;
struct TYPE_5__ {TYPE_1__* fh_dentry; } ;
struct nfsd3_readres {scalar_t__ count; int eof; TYPE_2__ fh; } ;
struct nfsd3_readargs {scalar_t__ count; scalar_t__ offset; int /*<<< orphan*/  vlen; int /*<<< orphan*/  fh; } ;
struct inode {scalar_t__ i_size; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_4__ {struct inode* d_inode; } ;

/* Variables and functions */
 int NFS3_POST_OP_ATTR_WORDS ; 
 int /*<<< orphan*/  RETURN_STATUS (scalar_t__) ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  fh_copy (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ nfsd_read (struct svc_rqst*,TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ svc_max_payload (struct svc_rqst*) ; 
 int /*<<< orphan*/  svc_reserve_auth (struct svc_rqst*,scalar_t__) ; 

__attribute__((used)) static __be32
nfsd3_proc_read(struct svc_rqst *rqstp, struct nfsd3_readargs *argp,
				        struct nfsd3_readres  *resp)
{
	__be32	nfserr;
	u32	max_blocksize = svc_max_payload(rqstp);

	dprintk("nfsd: READ(3) %s %lu bytes at %lu\n",
				SVCFH_fmt(&argp->fh),
				(unsigned long) argp->count,
				(unsigned long) argp->offset);

	/* Obtain buffer pointer for payload.
	 * 1 (status) + 22 (post_op_attr) + 1 (count) + 1 (eof)
	 * + 1 (xdr opaque byte count) = 26
	 */

	resp->count = argp->count;
	if (max_blocksize < resp->count)
		resp->count = max_blocksize;

	svc_reserve_auth(rqstp, ((1 + NFS3_POST_OP_ATTR_WORDS + 3)<<2) + resp->count +4);

	fh_copy(&resp->fh, &argp->fh);
	nfserr = nfsd_read(rqstp, &resp->fh,
				  argp->offset,
			   	  rqstp->rq_vec, argp->vlen,
				  &resp->count);
	if (nfserr == 0) {
		struct inode	*inode = resp->fh.fh_dentry->d_inode;

		resp->eof = (argp->offset + resp->count) >= inode->i_size;
	}

	RETURN_STATUS(nfserr);
}