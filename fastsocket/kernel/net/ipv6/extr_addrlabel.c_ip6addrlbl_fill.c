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
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct ip6addrlbl_entry {int /*<<< orphan*/  label; int /*<<< orphan*/  prefix; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  prefixlen; } ;
struct ifaddrlblmsg {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFAL_ADDRESS ; 
 int /*<<< orphan*/  IFAL_LABEL ; 
 int /*<<< orphan*/  ip6addrlbl_putmsg (struct nlmsghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 int nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int) ; 

__attribute__((used)) static int ip6addrlbl_fill(struct sk_buff *skb,
			   struct ip6addrlbl_entry *p,
			   u32 lseq,
			   u32 pid, u32 seq, int event,
			   unsigned int flags)
{
	struct nlmsghdr *nlh = nlmsg_put(skb, pid, seq, event,
					 sizeof(struct ifaddrlblmsg), flags);
	if (!nlh)
		return -EMSGSIZE;

	ip6addrlbl_putmsg(nlh, p->prefixlen, p->ifindex, lseq);

	if (nla_put(skb, IFAL_ADDRESS, 16, &p->prefix) < 0 ||
	    nla_put_u32(skb, IFAL_LABEL, p->label) < 0) {
		nlmsg_cancel(skb, nlh);
		return -EMSGSIZE;
	}

	return nlmsg_end(skb, nlh);
}