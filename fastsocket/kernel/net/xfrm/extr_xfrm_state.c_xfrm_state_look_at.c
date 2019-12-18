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
typedef  int /*<<< orphan*/  xfrm_address_t ;
struct TYPE_6__ {scalar_t__ family; } ;
struct TYPE_5__ {scalar_t__ state; scalar_t__ dying; } ;
struct TYPE_4__ {scalar_t__ add_time; } ;
struct xfrm_state {TYPE_3__ sel; TYPE_2__ km; TYPE_1__ curlft; } ;
struct xfrm_policy {int dummy; } ;
struct flowi {int dummy; } ;

/* Variables and functions */
 int ESRCH ; 
 scalar_t__ XFRM_STATE_ACQ ; 
 scalar_t__ XFRM_STATE_ERROR ; 
 scalar_t__ XFRM_STATE_EXPIRED ; 
 scalar_t__ XFRM_STATE_VALID ; 
 scalar_t__ security_xfrm_state_pol_flow_match (struct xfrm_state*,struct xfrm_policy*,struct flowi*) ; 
 scalar_t__ xfrm_selector_match (TYPE_3__*,struct flowi*,scalar_t__) ; 

__attribute__((used)) static void xfrm_state_look_at(struct xfrm_policy *pol, struct xfrm_state *x,
			       struct flowi *fl, unsigned short family,
			       xfrm_address_t *daddr, xfrm_address_t *saddr,
			       struct xfrm_state **best, int *acq_in_progress,
			       int *error)
{
	/* Resolution logic:
	 * 1. There is a valid state with matching selector. Done.
	 * 2. Valid state with inappropriate selector. Skip.
	 *
	 * Entering area of "sysdeps".
	 *
	 * 3. If state is not valid, selector is temporary, it selects
	 *    only session which triggered previous resolution. Key
	 *    manager will do something to install a state with proper
	 *    selector.
	 */
	if (x->km.state == XFRM_STATE_VALID) {
		if ((x->sel.family &&
		     !xfrm_selector_match(&x->sel, fl, x->sel.family)) ||
		    !security_xfrm_state_pol_flow_match(x, pol, fl))
			return;

		if (!*best ||
		    (*best)->km.dying > x->km.dying ||
		    ((*best)->km.dying == x->km.dying &&
		     (*best)->curlft.add_time < x->curlft.add_time))
			*best = x;
	} else if (x->km.state == XFRM_STATE_ACQ) {
		*acq_in_progress = 1;
	} else if (x->km.state == XFRM_STATE_ERROR ||
		   x->km.state == XFRM_STATE_EXPIRED) {
		if (xfrm_selector_match(&x->sel, fl, x->sel.family) &&
		    security_xfrm_state_pol_flow_match(x, pol, fl))
			*error = -ESRCH;
	}
}