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
struct rpcrdma_ia {int ri_memreg_strategy; TYPE_1__* ri_bind_mem; } ;
struct rpcrdma_xprt {struct rpcrdma_ia rx_ia; } ;
struct rpcrdma_mr_seg {int mr_nsegs; int /*<<< orphan*/  mr_dma; int /*<<< orphan*/  mr_base; int /*<<< orphan*/  mr_rkey; } ;
struct TYPE_2__ {int /*<<< orphan*/  rkey; } ;

/* Variables and functions */
#define  RPCRDMA_ALLPHYSICAL 132 
#define  RPCRDMA_FRMR 131 
#define  RPCRDMA_MEMWINDOWS 130 
#define  RPCRDMA_MEMWINDOWS_ASYNC 129 
#define  RPCRDMA_MTHCAFMR 128 
 int /*<<< orphan*/  rpcrdma_map_one (struct rpcrdma_ia*,struct rpcrdma_mr_seg*,int) ; 
 int rpcrdma_register_default_external (struct rpcrdma_mr_seg*,int*,int,struct rpcrdma_ia*) ; 
 int rpcrdma_register_fmr_external (struct rpcrdma_mr_seg*,int*,int,struct rpcrdma_ia*) ; 
 int rpcrdma_register_frmr_external (struct rpcrdma_mr_seg*,int*,int,struct rpcrdma_ia*,struct rpcrdma_xprt*) ; 
 int rpcrdma_register_memwin_external (struct rpcrdma_mr_seg*,int*,int,struct rpcrdma_ia*,struct rpcrdma_xprt*) ; 

int
rpcrdma_register_external(struct rpcrdma_mr_seg *seg,
			int nsegs, int writing, struct rpcrdma_xprt *r_xprt)
{
	struct rpcrdma_ia *ia = &r_xprt->rx_ia;
	int rc = 0;

	switch (ia->ri_memreg_strategy) {

#if RPCRDMA_PERSISTENT_REGISTRATION
	case RPCRDMA_ALLPHYSICAL:
		rpcrdma_map_one(ia, seg, writing);
		seg->mr_rkey = ia->ri_bind_mem->rkey;
		seg->mr_base = seg->mr_dma;
		seg->mr_nsegs = 1;
		nsegs = 1;
		break;
#endif

	/* Registration using frmr registration */
	case RPCRDMA_FRMR:
		rc = rpcrdma_register_frmr_external(seg, &nsegs, writing, ia, r_xprt);
		break;

	/* Registration using fmr memory registration */
	case RPCRDMA_MTHCAFMR:
		rc = rpcrdma_register_fmr_external(seg, &nsegs, writing, ia);
		break;

	/* Registration using memory windows */
	case RPCRDMA_MEMWINDOWS_ASYNC:
	case RPCRDMA_MEMWINDOWS:
		rc = rpcrdma_register_memwin_external(seg, &nsegs, writing, ia, r_xprt);
		break;

	/* Default registration each time */
	default:
		rc = rpcrdma_register_default_external(seg, &nsegs, writing, ia);
		break;
	}
	if (rc)
		return -1;

	return nsegs;
}