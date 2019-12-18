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
typedef  int /*<<< orphan*/  u8 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_len; int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t IPSET_ATTR_FAMILY ; 
 size_t IPSET_ATTR_PROTOCOL ; 
 size_t IPSET_ATTR_REVISION ; 
 size_t IPSET_ATTR_REVISION_MIN ; 
 size_t IPSET_ATTR_TYPENAME ; 
 int /*<<< orphan*/  IPSET_CMD_TYPE ; 
 int IPSET_ERR_PROTOCOL ; 
 int /*<<< orphan*/  IPSET_PROTOCOL ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLA_PUT_STRING (struct sk_buff*,size_t,char const*) ; 
 int /*<<< orphan*/  NLA_PUT_U8 (struct sk_buff*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int find_set_type_minmax (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int netlink_unicast (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* nla_data (struct nlattr const* const) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr const* const) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ protocol_failed (struct nlattr const* const*) ; 
 struct nlmsghdr* start_msg (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
ip_set_type(struct sock *ctnl, struct sk_buff *skb,
	    const struct nlmsghdr *nlh,
	    const struct nlattr * const attr[])
{
	struct sk_buff *skb2;
	struct nlmsghdr *nlh2;
	u8 family, min, max;
	const char *typename;
	int ret = 0;

	if (unlikely(protocol_failed(attr) ||
		     attr[IPSET_ATTR_TYPENAME] == NULL ||
		     attr[IPSET_ATTR_FAMILY] == NULL))
		return -IPSET_ERR_PROTOCOL;

	family = nla_get_u8(attr[IPSET_ATTR_FAMILY]);
	typename = nla_data(attr[IPSET_ATTR_TYPENAME]);
	ret = find_set_type_minmax(typename, family, &min, &max);
	if (ret)
		return ret;

	skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (skb2 == NULL)
		return -ENOMEM;

	nlh2 = start_msg(skb2, NETLINK_CB(skb).pid, nlh->nlmsg_seq, 0,
			 IPSET_CMD_TYPE);
	if (!nlh2)
		goto nlmsg_failure;
	NLA_PUT_U8(skb2, IPSET_ATTR_PROTOCOL, IPSET_PROTOCOL);
	NLA_PUT_STRING(skb2, IPSET_ATTR_TYPENAME, typename);
	NLA_PUT_U8(skb2, IPSET_ATTR_FAMILY, family);
	NLA_PUT_U8(skb2, IPSET_ATTR_REVISION, max);
	NLA_PUT_U8(skb2, IPSET_ATTR_REVISION_MIN, min);
	nlmsg_end(skb2, nlh2);

	pr_debug("Send TYPE, nlmsg_len: %u\n", nlh2->nlmsg_len);
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