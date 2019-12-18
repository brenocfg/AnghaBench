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
typedef  size_t u_int8_t ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {scalar_t__ nlmsg_len; int nlmsg_type; } ;
struct nlattr {int dummy; } ;
struct nfnl_callback {int (* call ) (int /*<<< orphan*/ ,struct sk_buff*,struct nlmsghdr*,struct nlattr const**) ;} ;
struct nfnetlink_subsystem {TYPE_1__* cb; } ;
struct nfgenmsg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  policy; int /*<<< orphan*/  attr_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EAGAIN ; 
 int EINVAL ; 
 int EPERM ; 
 size_t NFNL_MSG_TYPE (int) ; 
 int /*<<< orphan*/  NFNL_SUBSYS_ID (int) ; 
 scalar_t__ NLMSG_LENGTH (int) ; 
 int NLMSG_SPACE (int) ; 
 struct nfnl_callback* nfnetlink_find_client (int,struct nfnetlink_subsystem const*) ; 
 struct nfnetlink_subsystem* nfnetlink_get_subsys (int) ; 
 int /*<<< orphan*/  nfnl ; 
 int /*<<< orphan*/  nfnl_lock () ; 
 int /*<<< orphan*/  nfnl_unlock () ; 
 int nla_parse (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_module (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ security_netlink_recv (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,struct sk_buff*,struct nlmsghdr*,struct nlattr const**) ; 

__attribute__((used)) static int nfnetlink_rcv_msg(struct sk_buff *skb, struct nlmsghdr *nlh)
{
	const struct nfnl_callback *nc;
	const struct nfnetlink_subsystem *ss;
	int type, err;

	if (security_netlink_recv(skb, CAP_NET_ADMIN))
		return -EPERM;

	/* All the messages must at least contain nfgenmsg */
	if (nlh->nlmsg_len < NLMSG_LENGTH(sizeof(struct nfgenmsg)))
		return 0;

	type = nlh->nlmsg_type;
replay:
	ss = nfnetlink_get_subsys(type);
	if (!ss) {
#ifdef CONFIG_MODULES
		nfnl_unlock();
		request_module("nfnetlink-subsys-%d", NFNL_SUBSYS_ID(type));
		nfnl_lock();
		ss = nfnetlink_get_subsys(type);
		if (!ss)
#endif
			return -EINVAL;
	}

	nc = nfnetlink_find_client(type, ss);
	if (!nc)
		return -EINVAL;

	{
		int min_len = NLMSG_SPACE(sizeof(struct nfgenmsg));
		u_int8_t cb_id = NFNL_MSG_TYPE(nlh->nlmsg_type);
		struct nlattr *cda[ss->cb[cb_id].attr_count + 1];
		struct nlattr *attr = (void *)nlh + min_len;
		int attrlen = nlh->nlmsg_len - min_len;

		err = nla_parse(cda, ss->cb[cb_id].attr_count,
				attr, attrlen, ss->cb[cb_id].policy);
		if (err < 0)
			return err;

		err = nc->call(nfnl, skb, nlh, (const struct nlattr **)cda);
		if (err == -EAGAIN)
			goto replay;
		return err;
	}
}