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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  scalar_t__ u32 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int nlmsg_flags; int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct nfgenmsg {int /*<<< orphan*/  nfgen_family; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conntrack_expect {int dummy; } ;
struct netlink_dump_control {int /*<<< orphan*/  done; int /*<<< orphan*/  dump; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 size_t CTA_EXPECT_ID ; 
 size_t CTA_EXPECT_MASTER ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPCTNL_MSG_EXP_NEW ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int NLM_F_DUMP ; 
 int /*<<< orphan*/  ctnetlink_exp_done ; 
 int /*<<< orphan*/  ctnetlink_exp_dump_table ; 
 int ctnetlink_exp_fill_info (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nf_conntrack_expect*) ; 
 int ctnetlink_parse_tuple (struct nlattr const* const*,struct nf_conntrack_tuple*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int netlink_dump_start (struct sock*,struct sk_buff*,struct nlmsghdr const*,struct netlink_dump_control*) ; 
 int netlink_unicast (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nf_conntrack_expect* nf_ct_expect_find_get (int /*<<< orphan*/ *,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_ct_expect_put (struct nf_conntrack_expect*) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr const*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int
ctnetlink_get_expect(struct sock *ctnl, struct sk_buff *skb,
		     const struct nlmsghdr *nlh,
		     const struct nlattr * const cda[])
{
	struct nf_conntrack_tuple tuple;
	struct nf_conntrack_expect *exp;
	struct sk_buff *skb2;
	struct nfgenmsg *nfmsg = nlmsg_data(nlh);
	u_int8_t u3 = nfmsg->nfgen_family;
	int err = 0;

	if (nlh->nlmsg_flags & NLM_F_DUMP) {
		struct netlink_dump_control c = {
			.dump = ctnetlink_exp_dump_table,
			.done = ctnetlink_exp_done,
		};
		return netlink_dump_start(ctnl, skb, nlh, &c);
	}

	if (cda[CTA_EXPECT_MASTER])
		err = ctnetlink_parse_tuple(cda, &tuple, CTA_EXPECT_MASTER, u3);
	else
		return -EINVAL;

	if (err < 0)
		return err;

	exp = nf_ct_expect_find_get(&init_net, &tuple);
	if (!exp)
		return -ENOENT;

	if (cda[CTA_EXPECT_ID]) {
		__be32 id = nla_get_be32(cda[CTA_EXPECT_ID]);
		if (ntohl(id) != (u32)(unsigned long)exp) {
			nf_ct_expect_put(exp);
			return -ENOENT;
		}
	}

	err = -ENOMEM;
	skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (skb2 == NULL)
		goto out;

	rcu_read_lock();
	err = ctnetlink_exp_fill_info(skb2, NETLINK_CB(skb).pid,
				      nlh->nlmsg_seq, IPCTNL_MSG_EXP_NEW, exp);
	rcu_read_unlock();
	if (err <= 0)
		goto free;

	nf_ct_expect_put(exp);

	return netlink_unicast(ctnl, skb2, NETLINK_CB(skb).pid, MSG_DONTWAIT);

free:
	kfree_skb(skb2);
out:
	nf_ct_expect_put(exp);
	return err;
}