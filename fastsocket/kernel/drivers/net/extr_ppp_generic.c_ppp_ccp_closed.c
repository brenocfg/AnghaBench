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
struct ppp {int flags; int /*<<< orphan*/ * rc_state; struct compressor* rcomp; int /*<<< orphan*/  rstate; int /*<<< orphan*/ * xc_state; struct compressor* xcomp; int /*<<< orphan*/  xstate; } ;
struct compressor {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* decomp_free ) (void*) ;int /*<<< orphan*/  (* comp_free ) (void*) ;} ;

/* Variables and functions */
 int SC_CCP_OPEN ; 
 int SC_CCP_UP ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppp_lock (struct ppp*) ; 
 int /*<<< orphan*/  ppp_unlock (struct ppp*) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 

__attribute__((used)) static void
ppp_ccp_closed(struct ppp *ppp)
{
	void *xstate, *rstate;
	struct compressor *xcomp, *rcomp;

	ppp_lock(ppp);
	ppp->flags &= ~(SC_CCP_OPEN | SC_CCP_UP);
	ppp->xstate = 0;
	xcomp = ppp->xcomp;
	xstate = ppp->xc_state;
	ppp->xc_state = NULL;
	ppp->rstate = 0;
	rcomp = ppp->rcomp;
	rstate = ppp->rc_state;
	ppp->rc_state = NULL;
	ppp_unlock(ppp);

	if (xstate) {
		xcomp->comp_free(xstate);
		module_put(xcomp->owner);
	}
	if (rstate) {
		rcomp->decomp_free(rstate);
		module_put(rcomp->owner);
	}
}