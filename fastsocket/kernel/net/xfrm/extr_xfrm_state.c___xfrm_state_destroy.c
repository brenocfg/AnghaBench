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
struct TYPE_3__ {scalar_t__ state; } ;
struct xfrm_state {int /*<<< orphan*/  gclist; TYPE_1__ km; } ;
struct TYPE_4__ {int /*<<< orphan*/  state_gc_work; int /*<<< orphan*/  state_gc_list; } ;
struct net {TYPE_2__ xfrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ XFRM_STATE_DEAD ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_state_gc_lock ; 
 struct net* xs_net (struct xfrm_state*) ; 

void __xfrm_state_destroy(struct xfrm_state *x)
{
	struct net *net = xs_net(x);

	WARN_ON(x->km.state != XFRM_STATE_DEAD);

	spin_lock_bh(&xfrm_state_gc_lock);
	hlist_add_head(&x->gclist, &net->xfrm.state_gc_list);
	spin_unlock_bh(&xfrm_state_gc_lock);
	schedule_work(&net->xfrm.state_gc_work);
}