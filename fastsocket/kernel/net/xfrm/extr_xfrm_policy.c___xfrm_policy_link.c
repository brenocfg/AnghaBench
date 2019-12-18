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
struct TYPE_3__ {int /*<<< orphan*/  all; } ;
struct xfrm_policy {int /*<<< orphan*/  index; int /*<<< orphan*/  byidx; int /*<<< orphan*/  bydst; TYPE_1__ walk; int /*<<< orphan*/  family; int /*<<< orphan*/  selector; } ;
struct TYPE_4__ {int /*<<< orphan*/  policy_hash_work; int /*<<< orphan*/ * policy_count; struct hlist_head* policy_byidx; int /*<<< orphan*/  policy_all; } ;
struct net {TYPE_2__ xfrm; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 
 int idx_hash (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct hlist_head* policy_hash_bysel (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ xfrm_bydst_should_resize (struct net*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_pol_hold (struct xfrm_policy*) ; 
 struct net* xp_net (struct xfrm_policy*) ; 

__attribute__((used)) static void __xfrm_policy_link(struct xfrm_policy *pol, int dir)
{
	struct net *net = xp_net(pol);
	struct hlist_head *chain = policy_hash_bysel(net, &pol->selector,
						     pol->family, dir);

	list_add(&pol->walk.all, &net->xfrm.policy_all);
	hlist_add_head(&pol->bydst, chain);
	hlist_add_head(&pol->byidx, net->xfrm.policy_byidx+idx_hash(net, pol->index));
	net->xfrm.policy_count[dir]++;
	xfrm_pol_hold(pol);

	if (xfrm_bydst_should_resize(net, dir, NULL))
		schedule_work(&net->xfrm.policy_hash_work);
}