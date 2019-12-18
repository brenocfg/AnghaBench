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
struct xfrm_tmpl {int dummy; } ;
struct xfrm_state {int dummy; } ;
struct xfrm_policy {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nlsk; } ;
struct net {TYPE_1__ xfrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  XFRMNLGRP_ACQUIRE ; 
 scalar_t__ build_acquire (struct sk_buff*,struct xfrm_state*,struct xfrm_tmpl*,struct xfrm_policy*,int) ; 
 int nlmsg_multicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_acquire_msgsize (struct xfrm_state*,struct xfrm_policy*) ; 
 struct net* xs_net (struct xfrm_state*) ; 

__attribute__((used)) static int xfrm_send_acquire(struct xfrm_state *x, struct xfrm_tmpl *xt,
			     struct xfrm_policy *xp, int dir)
{
	struct net *net = xs_net(x);
	struct sk_buff *skb;

	skb = nlmsg_new(xfrm_acquire_msgsize(x, xp), GFP_ATOMIC);
	if (skb == NULL)
		return -ENOMEM;

	if (build_acquire(skb, x, xt, xp, dir) < 0)
		BUG();

	return nlmsg_multicast(net->xfrm.nlsk, skb, 0, XFRMNLGRP_ACQUIRE, GFP_ATOMIC);
}