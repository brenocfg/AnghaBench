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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct ifaddrmsg {int ifa_prefixlen; int ifa_flags; int /*<<< orphan*/  ifa_index; int /*<<< orphan*/  ifa_scope; int /*<<< orphan*/  ifa_family; } ;
struct dn_ifaddr {int ifa_flags; scalar_t__* ifa_label; scalar_t__ ifa_local; scalar_t__ ifa_address; TYPE_2__* ifa_dev; int /*<<< orphan*/  ifa_scope; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_DECnet ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFA_ADDRESS ; 
 int IFA_F_PERMANENT ; 
 int /*<<< orphan*/  IFA_LABEL ; 
 int /*<<< orphan*/  IFA_LOCAL ; 
 int /*<<< orphan*/  NLA_PUT_LE16 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NLA_PUT_STRING (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct ifaddrmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int) ; 

__attribute__((used)) static int dn_nl_fill_ifaddr(struct sk_buff *skb, struct dn_ifaddr *ifa,
			     u32 pid, u32 seq, int event, unsigned int flags)
{
	struct ifaddrmsg *ifm;
	struct nlmsghdr *nlh;

	nlh = nlmsg_put(skb, pid, seq, event, sizeof(*ifm), flags);
	if (nlh == NULL)
		return -EMSGSIZE;

	ifm = nlmsg_data(nlh);
	ifm->ifa_family = AF_DECnet;
	ifm->ifa_prefixlen = 16;
	ifm->ifa_flags = ifa->ifa_flags | IFA_F_PERMANENT;
	ifm->ifa_scope = ifa->ifa_scope;
	ifm->ifa_index = ifa->ifa_dev->dev->ifindex;

	if (ifa->ifa_address)
		NLA_PUT_LE16(skb, IFA_ADDRESS, ifa->ifa_address);
	if (ifa->ifa_local)
		NLA_PUT_LE16(skb, IFA_LOCAL, ifa->ifa_local);
	if (ifa->ifa_label[0])
		NLA_PUT_STRING(skb, IFA_LABEL, ifa->ifa_label);

	return nlmsg_end(skb, nlh);

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}