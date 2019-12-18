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
struct TYPE_3__ {scalar_t__ proto; } ;
struct xfrm_state {int /*<<< orphan*/  encap; TYPE_1__ id; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  nlsk; } ;
struct net {TYPE_2__ xfrm; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IPPROTO_ESP ; 
 int /*<<< orphan*/  XFRMNLGRP_MAPPING ; 
 scalar_t__ build_mapping (struct sk_buff*,struct xfrm_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nlmsg_multicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_mapping_msgsize () ; 
 struct net* xs_net (struct xfrm_state*) ; 

__attribute__((used)) static int xfrm_send_mapping(struct xfrm_state *x, xfrm_address_t *ipaddr,
			     __be16 sport)
{
	struct net *net = xs_net(x);
	struct sk_buff *skb;

	if (x->id.proto != IPPROTO_ESP)
		return -EINVAL;

	if (!x->encap)
		return -EINVAL;

	skb = nlmsg_new(xfrm_mapping_msgsize(), GFP_ATOMIC);
	if (skb == NULL)
		return -ENOMEM;

	if (build_mapping(skb, x, ipaddr, sport) < 0)
		BUG();

	return nlmsg_multicast(net->xfrm.nlsk, skb, 0, XFRMNLGRP_MAPPING, GFP_ATOMIC);
}