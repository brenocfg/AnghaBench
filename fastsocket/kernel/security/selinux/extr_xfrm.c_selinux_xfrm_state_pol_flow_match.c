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
typedef  scalar_t__ u32 ;
struct xfrm_state {TYPE_1__* security; } ;
struct xfrm_policy {int /*<<< orphan*/  security; } ;
struct flowi {scalar_t__ secid; } ;
struct TYPE_2__ {scalar_t__ ctx_sid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSOCIATION__SENDTO ; 
 int /*<<< orphan*/  SECCLASS_ASSOCIATION ; 
 scalar_t__ avc_has_perm (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selinux_authorizable_xfrm (struct xfrm_state*) ; 

int selinux_xfrm_state_pol_flow_match(struct xfrm_state *x, struct xfrm_policy *xp,
			struct flowi *fl)
{
	u32 state_sid;
	int rc;

	if (!xp->security)
		if (x->security)
			/* unlabeled policy and labeled SA can't match */
			return 0;
		else
			/* unlabeled policy and unlabeled SA match all flows */
			return 1;
	else
		if (!x->security)
			/* unlabeled SA and labeled policy can't match */
			return 0;
		else
			if (!selinux_authorizable_xfrm(x))
				/* Not a SELinux-labeled SA */
				return 0;

	state_sid = x->security->ctx_sid;

	if (fl->secid != state_sid)
		return 0;

	rc = avc_has_perm(fl->secid, state_sid, SECCLASS_ASSOCIATION,
			  ASSOCIATION__SENDTO,
			  NULL)? 0:1;

	/*
	 * We don't need a separate SA Vs. policy polmatch check
	 * since the SA is now of the same label as the flow and
	 * a flow Vs. policy polmatch check had already happened
	 * in selinux_xfrm_policy_lookup() above.
	 */

	return rc;
}