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
struct xfrm_tmpl {int dummy; } ;
struct xfrm_policy {int xfrm_nr; int /*<<< orphan*/  xfrm_vec; int /*<<< orphan*/  type; int /*<<< orphan*/  index; int /*<<< orphan*/  flags; int /*<<< orphan*/  action; int /*<<< orphan*/  mark; int /*<<< orphan*/  curlft; int /*<<< orphan*/  lft; int /*<<< orphan*/  security; int /*<<< orphan*/  selector; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ XFRM_POLICY_MAX ; 
 int /*<<< orphan*/  __xfrm_policy_link (struct xfrm_policy*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct xfrm_policy*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ security_xfrm_policy_clone (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_pol_put (struct xfrm_policy*) ; 
 struct xfrm_policy* xfrm_policy_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_policy_lock ; 
 int /*<<< orphan*/  xp_net (struct xfrm_policy*) ; 

__attribute__((used)) static struct xfrm_policy *clone_policy(struct xfrm_policy *old, int dir)
{
	struct xfrm_policy *newp = xfrm_policy_alloc(xp_net(old), GFP_ATOMIC);

	if (newp) {
		newp->selector = old->selector;
		if (security_xfrm_policy_clone(old->security,
					       &newp->security)) {
			kfree(newp);
			return NULL;  /* ENOMEM */
		}
		newp->lft = old->lft;
		newp->curlft = old->curlft;
		newp->mark = old->mark;
		newp->action = old->action;
		newp->flags = old->flags;
		newp->xfrm_nr = old->xfrm_nr;
		newp->index = old->index;
		newp->type = old->type;
		memcpy(newp->xfrm_vec, old->xfrm_vec,
		       newp->xfrm_nr*sizeof(struct xfrm_tmpl));
		write_lock_bh(&xfrm_policy_lock);
		__xfrm_policy_link(newp, XFRM_POLICY_MAX+dir);
		write_unlock_bh(&xfrm_policy_lock);
		xfrm_pol_put(newp);
	}
	return newp;
}