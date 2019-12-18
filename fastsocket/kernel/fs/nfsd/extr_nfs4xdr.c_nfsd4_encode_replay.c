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
struct nfsd4_op {int /*<<< orphan*/  opnum; struct nfs4_replay* replay; } ;
struct nfsd4_compoundres {int dummy; } ;
struct nfs4_replay {int rp_buflen; int /*<<< orphan*/  rp_buf; int /*<<< orphan*/  rp_status; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_ARGS () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RESERVE_SPACE (int) ; 
 int /*<<< orphan*/  WRITE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITEMEM (int /*<<< orphan*/ ,int) ; 

void
nfsd4_encode_replay(struct nfsd4_compoundres *resp, struct nfsd4_op *op)
{
	__be32 *p;
	struct nfs4_replay *rp = op->replay;

	BUG_ON(!rp);

	RESERVE_SPACE(8);
	WRITE32(op->opnum);
	*p++ = rp->rp_status;  /* already xdr'ed */
	ADJUST_ARGS();

	RESERVE_SPACE(rp->rp_buflen);
	WRITEMEM(rp->rp_buf, rp->rp_buflen);
	ADJUST_ARGS();
}