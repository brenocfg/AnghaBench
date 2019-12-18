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
struct sk_buff {int len; } ;
struct nlmsghdr {int nlmsg_flags; } ;

/* Variables and functions */
 struct nlmsghdr* NLMSG_NEXT (struct nlmsghdr*,int) ; 
 scalar_t__ NLMSG_OK (struct nlmsghdr*,int) ; 
 int NLM_F_ACK ; 
 int audit_receive_msg (struct sk_buff*,struct nlmsghdr*) ; 
 int /*<<< orphan*/  netlink_ack (struct sk_buff*,struct nlmsghdr*,int) ; 
 struct nlmsghdr* nlmsg_hdr (struct sk_buff*) ; 

__attribute__((used)) static void audit_receive_skb(struct sk_buff *skb)
{
	struct nlmsghdr *nlh;
	/*
	 * len MUST be signed for NLMSG_NEXT to be able to dec it below 0
	 * if the nlmsg_len was not aligned
	 */
	int len;
	int err;

	nlh = nlmsg_hdr(skb);
	len = skb->len;

	while (NLMSG_OK(nlh, len)) {
		err = audit_receive_msg(skb, nlh);
		/* if err or if this message says it wants a response */
		if (err || (nlh->nlmsg_flags & NLM_F_ACK))
			netlink_ack(skb, nlh, err);

		nlh = NLMSG_NEXT(nlh, len);
	}
}