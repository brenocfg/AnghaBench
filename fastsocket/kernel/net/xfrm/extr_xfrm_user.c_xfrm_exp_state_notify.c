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
struct xfrm_state {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nlsk; } ;
struct net {TYPE_1__ xfrm; } ;
struct km_event {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  XFRMNLGRP_EXPIRE ; 
 scalar_t__ build_expire (struct sk_buff*,struct xfrm_state*,struct km_event*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nlmsg_multicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_expire_msgsize () ; 
 struct net* xs_net (struct xfrm_state*) ; 

__attribute__((used)) static int xfrm_exp_state_notify(struct xfrm_state *x, struct km_event *c)
{
	struct net *net = xs_net(x);
	struct sk_buff *skb;

	skb = nlmsg_new(xfrm_expire_msgsize(), GFP_ATOMIC);
	if (skb == NULL)
		return -ENOMEM;

	if (build_expire(skb, x, c) < 0) {
		kfree_skb(skb);
		return -EMSGSIZE;
	}

	return nlmsg_multicast(net->xfrm.nlsk, skb, 0, XFRMNLGRP_EXPIRE, GFP_ATOMIC);
}