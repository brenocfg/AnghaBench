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
struct sk_buff {scalar_t__ pkt_type; int /*<<< orphan*/  dev; } ;
struct mld_msg {int /*<<< orphan*/  mld_mca; } ;
struct inet6_dev {int /*<<< orphan*/  lock; struct ifmcaddr6* mc_list; } ;
struct ifmcaddr6 {int mca_flags; int /*<<< orphan*/  mca_lock; int /*<<< orphan*/  mca_refcnt; int /*<<< orphan*/  mca_timer; int /*<<< orphan*/  mca_addr; struct ifmcaddr6* next; } ;
struct icmp6hdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int IPV6_ADDR_ANY ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int MAF_LAST_REPORTER ; 
 int MAF_TIMER_RUNNING ; 
 scalar_t__ PACKET_BROADCAST ; 
 scalar_t__ PACKET_LOOPBACK ; 
 scalar_t__ PACKET_MULTICAST ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ icmp6_hdr (struct sk_buff*) ; 
 struct inet6_dev* in6_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int igmp6_event_report(struct sk_buff *skb)
{
	struct ifmcaddr6 *ma;
	struct inet6_dev *idev;
	struct mld_msg *mld;
	int addr_type;

	/* Our own report looped back. Ignore it. */
	if (skb->pkt_type == PACKET_LOOPBACK)
		return 0;

	/* send our report if the MC router may not have heard this report */
	if (skb->pkt_type != PACKET_MULTICAST &&
	    skb->pkt_type != PACKET_BROADCAST)
		return 0;

	if (!pskb_may_pull(skb, sizeof(*mld) - sizeof(struct icmp6hdr)))
		return -EINVAL;

	mld = (struct mld_msg *)icmp6_hdr(skb);

	/* Drop reports with not link local source */
	addr_type = ipv6_addr_type(&ipv6_hdr(skb)->saddr);
	if (addr_type != IPV6_ADDR_ANY &&
	    !(addr_type&IPV6_ADDR_LINKLOCAL))
		return -EINVAL;

	idev = in6_dev_get(skb->dev);
	if (idev == NULL)
		return -ENODEV;

	/*
	 *	Cancel the timer for this group
	 */

	read_lock_bh(&idev->lock);
	for (ma = idev->mc_list; ma; ma=ma->next) {
		if (ipv6_addr_equal(&ma->mca_addr, &mld->mld_mca)) {
			spin_lock(&ma->mca_lock);
			if (del_timer(&ma->mca_timer))
				atomic_dec(&ma->mca_refcnt);
			ma->mca_flags &= ~(MAF_LAST_REPORTER|MAF_TIMER_RUNNING);
			spin_unlock(&ma->mca_lock);
			break;
		}
	}
	read_unlock_bh(&idev->lock);
	in6_dev_put(idev);
	return 0;
}