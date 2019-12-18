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
 int /*<<< orphan*/  BUG () ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  XFRMNLGRP_AEVENTS ; 
 scalar_t__ build_aevent (struct sk_buff*,struct xfrm_state*,struct km_event*) ; 
 int nlmsg_multicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_aevent_msgsize () ; 
 struct net* xs_net (struct xfrm_state*) ; 

__attribute__((used)) static int xfrm_aevent_state_notify(struct xfrm_state *x, struct km_event *c)
{
	struct net *net = xs_net(x);
	struct sk_buff *skb;

	skb = nlmsg_new(xfrm_aevent_msgsize(), GFP_ATOMIC);
	if (skb == NULL)
		return -ENOMEM;

	if (build_aevent(skb, x, c) < 0)
		BUG();

	return nlmsg_multicast(net->xfrm.nlsk, skb, 0, XFRMNLGRP_AEVENTS, GFP_ATOMIC);
}