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
struct xfrm_policy {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nlsk; } ;
struct net {TYPE_1__ xfrm; } ;
struct km_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  XFRMNLGRP_EXPIRE ; 
 scalar_t__ build_polexpire (struct sk_buff*,struct xfrm_policy*,int,struct km_event*) ; 
 int nlmsg_multicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_polexpire_msgsize (struct xfrm_policy*) ; 
 struct net* xp_net (struct xfrm_policy*) ; 

__attribute__((used)) static int xfrm_exp_policy_notify(struct xfrm_policy *xp, int dir, struct km_event *c)
{
	struct net *net = xp_net(xp);
	struct sk_buff *skb;

	skb = nlmsg_new(xfrm_polexpire_msgsize(xp), GFP_ATOMIC);
	if (skb == NULL)
		return -ENOMEM;

	if (build_polexpire(skb, xp, dir, c) < 0)
		BUG();

	return nlmsg_multicast(net->xfrm.nlsk, skb, 0, XFRMNLGRP_EXPIRE, GFP_ATOMIC);
}