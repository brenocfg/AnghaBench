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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t IPSET_ATTR_PROTOCOL ; 
 int /*<<< orphan*/  IPSET_CMD_PROTOCOL ; 
 int IPSET_ERR_PROTOCOL ; 
 int /*<<< orphan*/  IPSET_PROTOCOL ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLA_PUT_U8 (struct sk_buff*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int netlink_unicast (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nlmsghdr* start_msg (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ip_set_protocol(struct sock *ctnl, struct sk_buff *skb,
		const struct nlmsghdr *nlh,
		const struct nlattr * const attr[])
{
	struct sk_buff *skb2;
	struct nlmsghdr *nlh2;
	int ret = 0;

	if (unlikely(attr[IPSET_ATTR_PROTOCOL] == NULL))
		return -IPSET_ERR_PROTOCOL;

	skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (skb2 == NULL)
		return -ENOMEM;

	nlh2 = start_msg(skb2, NETLINK_CB(skb).pid, nlh->nlmsg_seq, 0,
			 IPSET_CMD_PROTOCOL);
	if (!nlh2)
		goto nlmsg_failure;
	NLA_PUT_U8(skb2, IPSET_ATTR_PROTOCOL, IPSET_PROTOCOL);
	nlmsg_end(skb2, nlh2);

	ret = netlink_unicast(ctnl, skb2, NETLINK_CB(skb).pid, MSG_DONTWAIT);
	if (ret < 0)
		return ret;

	return 0;

nla_put_failure:
	nlmsg_cancel(skb2, nlh2);
nlmsg_failure:
	kfree_skb(skb2);
	return -EMSGSIZE;
}