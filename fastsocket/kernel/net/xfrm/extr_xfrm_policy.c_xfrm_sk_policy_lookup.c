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
struct TYPE_2__ {int m; int v; } ;
struct xfrm_policy {int /*<<< orphan*/  security; TYPE_1__ mark; int /*<<< orphan*/  selector; } ;
struct sock {int sk_mark; int /*<<< orphan*/  sk_family; struct xfrm_policy** sk_policy; } ;
struct flowi {int /*<<< orphan*/  secid; } ;

/* Variables and functions */
 struct xfrm_policy* ERR_PTR (int) ; 
 int ESRCH ; 
 int /*<<< orphan*/  policy_to_flow_dir (int) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int security_xfrm_policy_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_pol_hold (struct xfrm_policy*) ; 
 int /*<<< orphan*/  xfrm_policy_lock ; 
 int xfrm_selector_match (int /*<<< orphan*/ *,struct flowi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xfrm_policy *xfrm_sk_policy_lookup(struct sock *sk, int dir, struct flowi *fl)
{
	struct xfrm_policy *pol;

	read_lock_bh(&xfrm_policy_lock);
	if ((pol = sk->sk_policy[dir]) != NULL) {
		int match = xfrm_selector_match(&pol->selector, fl,
						sk->sk_family);
		int err = 0;

		if (match) {
			if ((sk->sk_mark & pol->mark.m) != pol->mark.v) {
				pol = NULL;
				goto out;
			}
			err = security_xfrm_policy_lookup(pol->security,
						      fl->secid,
						      policy_to_flow_dir(dir));
			if (!err)
				xfrm_pol_hold(pol);
			else if (err == -ESRCH)
				pol = NULL;
			else
				pol = ERR_PTR(err);
		} else
			pol = NULL;
	}
out:
	read_unlock_bh(&xfrm_policy_lock);
	return pol;
}