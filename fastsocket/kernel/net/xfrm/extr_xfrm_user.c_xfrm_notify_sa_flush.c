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
struct xfrm_usersa_flush {int /*<<< orphan*/  proto; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  nlsk; } ;
struct net {TYPE_2__ xfrm; } ;
struct TYPE_3__ {int /*<<< orphan*/  proto; } ;
struct km_event {TYPE_1__ data; int /*<<< orphan*/  seq; int /*<<< orphan*/  pid; struct net* net; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NLMSG_ALIGN (int) ; 
 int /*<<< orphan*/  XFRMNLGRP_SA ; 
 int /*<<< orphan*/  XFRM_MSG_FLUSHSA ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct xfrm_usersa_flush* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 int nlmsg_multicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nlmsg_new (int,int /*<<< orphan*/ ) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xfrm_notify_sa_flush(struct km_event *c)
{
	struct net *net = c->net;
	struct xfrm_usersa_flush *p;
	struct nlmsghdr *nlh;
	struct sk_buff *skb;
	int len = NLMSG_ALIGN(sizeof(struct xfrm_usersa_flush));

	skb = nlmsg_new(len, GFP_ATOMIC);
	if (skb == NULL)
		return -ENOMEM;

	nlh = nlmsg_put(skb, c->pid, c->seq, XFRM_MSG_FLUSHSA, sizeof(*p), 0);
	if (nlh == NULL) {
		kfree_skb(skb);
		return -EMSGSIZE;
	}

	p = nlmsg_data(nlh);
	p->proto = c->data.proto;

	nlmsg_end(skb, nlh);

	return nlmsg_multicast(net->xfrm.nlsk, skb, 0, XFRMNLGRP_SA, GFP_ATOMIC);
}