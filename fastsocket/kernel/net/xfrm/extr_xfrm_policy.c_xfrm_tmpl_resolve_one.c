#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfrm_address_t ;
struct TYPE_3__ {int /*<<< orphan*/  daddr; } ;
struct xfrm_tmpl {scalar_t__ mode; unsigned short encap_family; int /*<<< orphan*/  optional; int /*<<< orphan*/  saddr; TYPE_1__ id; } ;
struct TYPE_4__ {scalar_t__ state; } ;
struct xfrm_state {TYPE_2__ km; } ;
struct xfrm_policy {int xfrm_nr; struct xfrm_tmpl* xfrm_vec; } ;
struct net {int dummy; } ;
struct flowi {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ESRCH ; 
 scalar_t__ XFRM_MODE_BEET ; 
 scalar_t__ XFRM_MODE_TUNNEL ; 
 scalar_t__ XFRM_STATE_ERROR ; 
 scalar_t__ XFRM_STATE_VALID ; 
 scalar_t__ xfrm_addr_any (int /*<<< orphan*/ *,unsigned short) ; 
 int /*<<< orphan*/ * xfrm_flowi_daddr (struct flowi*,unsigned short) ; 
 int /*<<< orphan*/ * xfrm_flowi_saddr (struct flowi*,unsigned short) ; 
 int xfrm_get_saddr (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned short) ; 
 struct xfrm_state* xfrm_state_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct flowi*,struct xfrm_tmpl*,struct xfrm_policy*,int*,unsigned short) ; 
 int /*<<< orphan*/  xfrm_state_put (struct xfrm_state*) ; 
 struct net* xp_net (struct xfrm_policy*) ; 

__attribute__((used)) static int
xfrm_tmpl_resolve_one(struct xfrm_policy *policy, struct flowi *fl,
		      struct xfrm_state **xfrm,
		      unsigned short family)
{
	struct net *net = xp_net(policy);
	int nx;
	int i, error;
	xfrm_address_t *daddr = xfrm_flowi_daddr(fl, family);
	xfrm_address_t *saddr = xfrm_flowi_saddr(fl, family);
	xfrm_address_t tmp;

	for (nx=0, i = 0; i < policy->xfrm_nr; i++) {
		struct xfrm_state *x;
		xfrm_address_t *remote = daddr;
		xfrm_address_t *local  = saddr;
		struct xfrm_tmpl *tmpl = &policy->xfrm_vec[i];

		if (tmpl->mode == XFRM_MODE_TUNNEL ||
		    tmpl->mode == XFRM_MODE_BEET) {
			remote = &tmpl->id.daddr;
			local = &tmpl->saddr;
			family = tmpl->encap_family;
			if (xfrm_addr_any(local, family)) {
				error = xfrm_get_saddr(net, &tmp, remote, family);
				if (error)
					goto fail;
				local = &tmp;
			}
		}

		x = xfrm_state_find(remote, local, fl, tmpl, policy, &error, family);

		if (x && x->km.state == XFRM_STATE_VALID) {
			xfrm[nx++] = x;
			daddr = remote;
			saddr = local;
			continue;
		}
		if (x) {
			error = (x->km.state == XFRM_STATE_ERROR ?
				 -EINVAL : -EAGAIN);
			xfrm_state_put(x);
		}
		else if (error == -ESRCH)
			error = -EAGAIN;

		if (!tmpl->optional)
			goto fail;
	}
	return nx;

fail:
	for (nx--; nx>=0; nx--)
		xfrm_state_put(xfrm[nx]);
	return error;
}