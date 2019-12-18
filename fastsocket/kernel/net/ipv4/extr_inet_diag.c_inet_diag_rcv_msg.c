#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nlmsghdr {scalar_t__ nlmsg_type; int nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct netlink_dump_control {int /*<<< orphan*/  dump; } ;
struct inet_diag_req {int dummy; } ;
struct inet_diag_bc_op {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ INET_DIAG_GETSOCK_MAX ; 
 int /*<<< orphan*/  INET_DIAG_REQ_BYTECODE ; 
 int NLM_F_DUMP ; 
 int /*<<< orphan*/  idiagnl ; 
 scalar_t__ inet_diag_bc_audit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inet_diag_dump ; 
 int inet_diag_get_exact (struct sk_buff*,struct nlmsghdr*) ; 
 int netlink_dump_start (int /*<<< orphan*/ ,struct sk_buff*,struct nlmsghdr*,struct netlink_dump_control*) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 scalar_t__ nlmsg_attrlen (struct nlmsghdr*,int) ; 
 struct nlattr* nlmsg_find_attr (struct nlmsghdr*,int,int /*<<< orphan*/ ) ; 
 int nlmsg_len (struct nlmsghdr*) ; 

__attribute__((used)) static int inet_diag_rcv_msg(struct sk_buff *skb, struct nlmsghdr *nlh)
{
	int hdrlen = sizeof(struct inet_diag_req);

	if (nlh->nlmsg_type >= INET_DIAG_GETSOCK_MAX ||
	    nlmsg_len(nlh) < hdrlen)
		return -EINVAL;

	if (nlh->nlmsg_flags & NLM_F_DUMP) {
		if (nlmsg_attrlen(nlh, hdrlen)) {
			struct nlattr *attr;

			attr = nlmsg_find_attr(nlh, hdrlen,
					       INET_DIAG_REQ_BYTECODE);
			if (attr == NULL ||
			    nla_len(attr) < sizeof(struct inet_diag_bc_op) ||
			    inet_diag_bc_audit(nla_data(attr), nla_len(attr)))
				return -EINVAL;
		}
		{
			struct netlink_dump_control c = {
				.dump = inet_diag_dump,
			};
			return netlink_dump_start(idiagnl, skb, nlh, &c);
		}
	}

	return inet_diag_get_exact(skb, nlh);
}