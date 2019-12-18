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
struct TYPE_2__ {int /*<<< orphan*/  add_time; } ;
struct xfrm_policy {scalar_t__ type; int /*<<< orphan*/  index; TYPE_1__ curlft; } ;
struct sock {struct xfrm_policy** sk_policy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ XFRM_POLICY_MAX ; 
 scalar_t__ XFRM_POLICY_TYPE_MAIN ; 
 int /*<<< orphan*/  __xfrm_policy_link (struct xfrm_policy*,scalar_t__) ; 
 int /*<<< orphan*/  __xfrm_policy_unlink (struct xfrm_policy*,scalar_t__) ; 
 int /*<<< orphan*/  get_seconds () ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_gen_index (struct net*,scalar_t__) ; 
 int /*<<< orphan*/  xfrm_policy_kill (struct xfrm_policy*) ; 
 int /*<<< orphan*/  xfrm_policy_lock ; 
 struct net* xp_net (struct xfrm_policy*) ; 

int xfrm_sk_policy_insert(struct sock *sk, int dir, struct xfrm_policy *pol)
{
	struct net *net = xp_net(pol);
	struct xfrm_policy *old_pol;

#ifdef CONFIG_XFRM_SUB_POLICY
	if (pol && pol->type != XFRM_POLICY_TYPE_MAIN)
		return -EINVAL;
#endif

	write_lock_bh(&xfrm_policy_lock);
	old_pol = sk->sk_policy[dir];
	sk->sk_policy[dir] = pol;
	if (pol) {
		pol->curlft.add_time = get_seconds();
		pol->index = xfrm_gen_index(net, XFRM_POLICY_MAX+dir);
		__xfrm_policy_link(pol, XFRM_POLICY_MAX+dir);
	}
	if (old_pol)
		/* Unlinking succeeds always. This is the only function
		 * allowed to delete or replace socket policy.
		 */
		__xfrm_policy_unlink(old_pol, XFRM_POLICY_MAX+dir);
	write_unlock_bh(&xfrm_policy_lock);

	if (old_pol) {
		xfrm_policy_kill(old_pol);
	}
	return 0;
}