#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xfrm_usersa_info {int dummy; } ;
struct xfrm_usersa_id {int /*<<< orphan*/  proto; int /*<<< orphan*/  family; int /*<<< orphan*/  spi; int /*<<< orphan*/  daddr; } ;
struct TYPE_5__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  spi; int /*<<< orphan*/  daddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  family; } ;
struct xfrm_state {TYPE_2__ id; TYPE_1__ props; } ;
struct xfrm_mark {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  nlsk; } ;
struct net {TYPE_3__ xfrm; } ;
struct km_event {int /*<<< orphan*/  event; int /*<<< orphan*/  seq; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ NLMSG_ALIGN (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  XFRMA_SA ; 
 int /*<<< orphan*/  XFRMNLGRP_SA ; 
 int /*<<< orphan*/  XFRM_MSG_DELSA ; 
 scalar_t__ copy_to_user_state_extra (struct xfrm_state*,struct xfrm_usersa_info*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct xfrm_usersa_info* nla_data (struct nlattr*) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nla_total_size (int) ; 
 void* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 int nlmsg_multicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nlmsg_new (int,int /*<<< orphan*/ ) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int xfrm_sa_len (struct xfrm_state*) ; 
 struct net* xs_net (struct xfrm_state*) ; 

__attribute__((used)) static int xfrm_notify_sa(struct xfrm_state *x, struct km_event *c)
{
	struct net *net = xs_net(x);
	struct xfrm_usersa_info *p;
	struct xfrm_usersa_id *id;
	struct nlmsghdr *nlh;
	struct sk_buff *skb;
	int len = xfrm_sa_len(x);
	int headlen;

	headlen = sizeof(*p);
	if (c->event == XFRM_MSG_DELSA) {
		len += nla_total_size(headlen);
		headlen = sizeof(*id);
		len += nla_total_size(sizeof(struct xfrm_mark));
	}
	len += NLMSG_ALIGN(headlen);

	skb = nlmsg_new(len, GFP_ATOMIC);
	if (skb == NULL)
		return -ENOMEM;

	nlh = nlmsg_put(skb, c->pid, c->seq, c->event, headlen, 0);
	if (nlh == NULL)
		goto nla_put_failure;

	p = nlmsg_data(nlh);
	if (c->event == XFRM_MSG_DELSA) {
		struct nlattr *attr;

		id = nlmsg_data(nlh);
		memcpy(&id->daddr, &x->id.daddr, sizeof(id->daddr));
		id->spi = x->id.spi;
		id->family = x->props.family;
		id->proto = x->id.proto;

		attr = nla_reserve(skb, XFRMA_SA, sizeof(*p));
		if (attr == NULL)
			goto nla_put_failure;

		p = nla_data(attr);
	}

	if (copy_to_user_state_extra(x, p, skb))
		goto nla_put_failure;

	nlmsg_end(skb, nlh);

	return nlmsg_multicast(net->xfrm.nlsk, skb, 0, XFRMNLGRP_SA, GFP_ATOMIC);

nla_put_failure:
	/* Somebody screwed up with xfrm_sa_len! */
	WARN_ON(1);
	kfree_skb(skb);
	return -1;
}