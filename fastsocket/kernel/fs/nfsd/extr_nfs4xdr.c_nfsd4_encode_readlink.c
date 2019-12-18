#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nfsd4_readlink {int /*<<< orphan*/  rl_fhp; int /*<<< orphan*/  rl_rqstp; } ;
struct nfsd4_compoundres {TYPE_4__* xbuf; TYPE_1__* rqstp; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_8__ {int page_len; TYPE_3__* tail; TYPE_2__* head; } ;
struct TYPE_7__ {int iov_len; int /*<<< orphan*/ * iov_base; } ;
struct TYPE_6__ {int iov_len; scalar_t__ iov_base; } ;
struct TYPE_5__ {int /*<<< orphan*/  rq_resused; int /*<<< orphan*/ * rq_respages; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_ARGS () ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  RESERVE_SPACE (int) ; 
 int /*<<< orphan*/  WRITE32 (int) ; 
 int /*<<< orphan*/  nfsd_readlink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  nfserr_inval ; 
 int /*<<< orphan*/  nfserr_isdir ; 
 int /*<<< orphan*/  nfserr_resource ; 
 char* page_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32
nfsd4_encode_readlink(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_readlink *readlink)
{
	int maxcount;
	char *page;
	__be32 *p;

	if (nfserr)
		return nfserr;
	if (resp->xbuf->page_len)
		return nfserr_resource;

	page = page_address(resp->rqstp->rq_respages[resp->rqstp->rq_resused++]);

	maxcount = PAGE_SIZE;
	RESERVE_SPACE(4);

	/*
	 * XXX: By default, the ->readlink() VFS op will truncate symlinks
	 * if they would overflow the buffer.  Is this kosher in NFSv4?  If
	 * not, one easy fix is: if ->readlink() precisely fills the buffer,
	 * assume that truncation occurred, and return NFS4ERR_RESOURCE.
	 */
	nfserr = nfsd_readlink(readlink->rl_rqstp, readlink->rl_fhp, page, &maxcount);
	if (nfserr == nfserr_isdir)
		return nfserr_inval;
	if (nfserr)
		return nfserr;

	WRITE32(maxcount);
	ADJUST_ARGS();
	resp->xbuf->head[0].iov_len = (char*)p
				- (char*)resp->xbuf->head[0].iov_base;
	resp->xbuf->page_len = maxcount;

	/* Use rest of head for padding and remaining ops: */
	resp->xbuf->tail[0].iov_base = p;
	resp->xbuf->tail[0].iov_len = 0;
	if (maxcount&3) {
		RESERVE_SPACE(4);
		WRITE32(0);
		resp->xbuf->tail[0].iov_base += maxcount&3;
		resp->xbuf->tail[0].iov_len = 4 - (maxcount&3);
		ADJUST_ARGS();
	}
	return 0;
}