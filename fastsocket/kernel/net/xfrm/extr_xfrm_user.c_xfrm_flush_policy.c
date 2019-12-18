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
typedef  int /*<<< orphan*/  u8 ;
struct xfrm_audit {int /*<<< orphan*/  secid; int /*<<< orphan*/  sessionid; int /*<<< orphan*/  loginuid; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_pid; int /*<<< orphan*/  nlmsg_seq; int /*<<< orphan*/  nlmsg_type; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct km_event {struct net* net; int /*<<< orphan*/  pid; int /*<<< orphan*/  seq; int /*<<< orphan*/  event; TYPE_1__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  sid; int /*<<< orphan*/  sessionid; int /*<<< orphan*/  loginuid; } ;

/* Variables and functions */
 int ESRCH ; 
 TYPE_2__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  XFRM_POLICY_TYPE_MAIN ; 
 int copy_from_user_policy_type (int /*<<< orphan*/ *,struct nlattr**) ; 
 int /*<<< orphan*/  km_policy_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct km_event*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int xfrm_policy_flush (struct net*,int /*<<< orphan*/ ,struct xfrm_audit*) ; 

__attribute__((used)) static int xfrm_flush_policy(struct sk_buff *skb, struct nlmsghdr *nlh,
		struct nlattr **attrs)
{
	struct net *net = sock_net(skb->sk);
	struct km_event c;
	u8 type = XFRM_POLICY_TYPE_MAIN;
	int err;
	struct xfrm_audit audit_info;

	err = copy_from_user_policy_type(&type, attrs);
	if (err)
		return err;

	audit_info.loginuid = NETLINK_CB(skb).loginuid;
	audit_info.sessionid = NETLINK_CB(skb).sessionid;
	audit_info.secid = NETLINK_CB(skb).sid;
	err = xfrm_policy_flush(net, type, &audit_info);
	if (err) {
		if (err == -ESRCH) /* empty table */
			return 0;
		return err;
	}

	c.data.type = type;
	c.event = nlh->nlmsg_type;
	c.seq = nlh->nlmsg_seq;
	c.pid = nlh->nlmsg_pid;
	c.net = net;
	km_policy_notify(NULL, 0, &c);
	return 0;
}