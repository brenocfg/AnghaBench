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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct net {struct sock* genl_sock; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  nlmsg_notify (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int nlmsg_report (struct nlmsghdr*) ; 

void genl_notify(struct sk_buff *skb, struct net *net, u32 pid, u32 group,
		 struct nlmsghdr *nlh, gfp_t flags)
{
	struct sock *sk = net->genl_sock;
	int report = 0;

	if (nlh)
		report = nlmsg_report(nlh);

	nlmsg_notify(sk, skb, pid, group, report, flags);
}