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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct ip_set {TYPE_1__* type; int /*<<< orphan*/  family; int /*<<< orphan*/  name; } ;
typedef  size_t ip_set_id_t ;
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;
struct TYPE_3__ {int /*<<< orphan*/  revision; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPSET_ATTR_FAMILY ; 
 int /*<<< orphan*/  IPSET_ATTR_PROTOCOL ; 
 int /*<<< orphan*/  IPSET_ATTR_REVISION ; 
 size_t IPSET_ATTR_SETNAME ; 
 size_t IPSET_ATTR_TYPENAME ; 
 int /*<<< orphan*/  IPSET_CMD_HEADER ; 
 int IPSET_ERR_PROTOCOL ; 
 size_t IPSET_INVALID_ID ; 
 int /*<<< orphan*/  IPSET_PROTOCOL ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 TYPE_2__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLA_PUT_STRING (struct sk_buff*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLA_PUT_U8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 size_t find_set_id (int /*<<< orphan*/ ) ; 
 struct ip_set** ip_set_list ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int netlink_unicast (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_data (struct nlattr const* const) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ protocol_failed (struct nlattr const* const*) ; 
 struct nlmsghdr* start_msg (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
ip_set_header(struct sock *ctnl, struct sk_buff *skb,
	      const struct nlmsghdr *nlh,
	      const struct nlattr * const attr[])
{
	const struct ip_set *set;
	struct sk_buff *skb2;
	struct nlmsghdr *nlh2;
	ip_set_id_t index;
	int ret = 0;

	if (unlikely(protocol_failed(attr) ||
		     attr[IPSET_ATTR_SETNAME] == NULL))
		return -IPSET_ERR_PROTOCOL;

	index = find_set_id(nla_data(attr[IPSET_ATTR_SETNAME]));
	if (index == IPSET_INVALID_ID)
		return -ENOENT;
	set = ip_set_list[index];

	skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (skb2 == NULL)
		return -ENOMEM;

	nlh2 = start_msg(skb2, NETLINK_CB(skb).pid, nlh->nlmsg_seq, 0,
			 IPSET_CMD_HEADER);
	if (!nlh2)
		goto nlmsg_failure;
	NLA_PUT_U8(skb2, IPSET_ATTR_PROTOCOL, IPSET_PROTOCOL);
	NLA_PUT_STRING(skb2, IPSET_ATTR_SETNAME, set->name);
	NLA_PUT_STRING(skb2, IPSET_ATTR_TYPENAME, set->type->name);
	NLA_PUT_U8(skb2, IPSET_ATTR_FAMILY, set->family);
	NLA_PUT_U8(skb2, IPSET_ATTR_REVISION, set->type->revision);
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