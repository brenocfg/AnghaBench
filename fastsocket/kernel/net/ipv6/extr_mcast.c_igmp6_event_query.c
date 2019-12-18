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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct in6_addr {int dummy; } ;
struct mld_msg {scalar_t__ mld_maxdelay; struct in6_addr mld_mca; } ;
struct mld2_query {scalar_t__ mld2q_mrc; int mld2q_qrv; scalar_t__ mld2q_nsrcs; int /*<<< orphan*/  mld2q_srcs; } ;
struct ipv6hdr {int dummy; } ;
struct inet6_dev {int mc_qrv; unsigned long mc_maxdelay; int /*<<< orphan*/  lock; struct ifmcaddr6* mc_list; int /*<<< orphan*/  mc_ifc_timer; scalar_t__ mc_ifc_count; scalar_t__ mc_v1_seen; } ;
struct ifmcaddr6 {int mca_flags; int /*<<< orphan*/  mca_lock; int /*<<< orphan*/  mca_addr; struct ifmcaddr6* next; } ;
struct icmp6hdr {int dummy; } ;
struct TYPE_2__ {scalar_t__ payload_len; struct in6_addr saddr; } ;

/* Variables and functions */
 int EINVAL ; 
 int HZ ; 
 int IPV6_ADDR_ANY ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int IPV6_ADDR_MULTICAST ; 
 int MAF_GSQUERY ; 
 int MAF_TIMER_RUNNING ; 
 int MLDV2_MRC (int) ; 
 int /*<<< orphan*/  __in6_dev_put (struct inet6_dev*) ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ icmp6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  igmp6_group_queried (struct ifmcaddr6*,unsigned long) ; 
 struct inet6_dev* in6_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 int /*<<< orphan*/  ipv6_addr_equal (struct in6_addr*,int /*<<< orphan*/ *) ; 
 int ipv6_addr_type (struct in6_addr*) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mld_clear_delrec (struct inet6_dev*) ; 
 int /*<<< orphan*/  mld_gq_start_timer (struct inet6_dev*) ; 
 scalar_t__ mld_marksources (struct ifmcaddr6*,int,int /*<<< orphan*/ ) ; 
 int ntohs (scalar_t__) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_network_header_len (struct sk_buff*) ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int igmp6_event_query(struct sk_buff *skb)
{
	struct mld2_query *mlh2 = NULL;
	struct ifmcaddr6 *ma;
	struct in6_addr *group;
	unsigned long max_delay;
	struct inet6_dev *idev;
	struct mld_msg *mld;
	int group_type;
	int mark = 0;
	int len;

	if (!pskb_may_pull(skb, sizeof(struct in6_addr)))
		return -EINVAL;

	/* compute payload length excluding extension headers */
	len = ntohs(ipv6_hdr(skb)->payload_len) + sizeof(struct ipv6hdr);
	len -= skb_network_header_len(skb);

	/* Drop queries with not link local source */
	if (!(ipv6_addr_type(&ipv6_hdr(skb)->saddr) & IPV6_ADDR_LINKLOCAL))
		return -EINVAL;

	idev = in6_dev_get(skb->dev);

	if (idev == NULL)
		return 0;

	mld = (struct mld_msg *)icmp6_hdr(skb);
	group = &mld->mld_mca;
	group_type = ipv6_addr_type(group);

	if (group_type != IPV6_ADDR_ANY &&
	    !(group_type&IPV6_ADDR_MULTICAST)) {
		in6_dev_put(idev);
		return -EINVAL;
	}

	if (len == 24) {
		int switchback;
		/* MLDv1 router present */

		/* Translate milliseconds to jiffies */
		max_delay = (ntohs(mld->mld_maxdelay)*HZ)/1000;

		switchback = (idev->mc_qrv + 1) * max_delay;
		idev->mc_v1_seen = jiffies + switchback;

		/* cancel the interface change timer */
		idev->mc_ifc_count = 0;
		if (del_timer(&idev->mc_ifc_timer))
			__in6_dev_put(idev);
		/* clear deleted report items */
		mld_clear_delrec(idev);
	} else if (len >= 28) {
		int srcs_offset = sizeof(struct mld2_query) -
				  sizeof(struct icmp6hdr);
		if (!pskb_may_pull(skb, srcs_offset)) {
			in6_dev_put(idev);
			return -EINVAL;
		}
		mlh2 = (struct mld2_query *)skb_transport_header(skb);
		max_delay = (MLDV2_MRC(ntohs(mlh2->mld2q_mrc))*HZ)/1000;
		if (!max_delay)
			max_delay = 1;
		idev->mc_maxdelay = max_delay;
		if (mlh2->mld2q_qrv)
			idev->mc_qrv = mlh2->mld2q_qrv;
		if (group_type == IPV6_ADDR_ANY) { /* general query */
			if (mlh2->mld2q_nsrcs) {
				in6_dev_put(idev);
				return -EINVAL; /* no sources allowed */
			}
			mld_gq_start_timer(idev);
			in6_dev_put(idev);
			return 0;
		}
		/* mark sources to include, if group & source-specific */
		if (mlh2->mld2q_nsrcs != 0) {
			if (!pskb_may_pull(skb, srcs_offset +
			    ntohs(mlh2->mld2q_nsrcs) * sizeof(struct in6_addr))) {
				in6_dev_put(idev);
				return -EINVAL;
			}
			mlh2 = (struct mld2_query *)skb_transport_header(skb);
			mark = 1;
		}
	} else {
		in6_dev_put(idev);
		return -EINVAL;
	}

	read_lock_bh(&idev->lock);
	if (group_type == IPV6_ADDR_ANY) {
		for (ma = idev->mc_list; ma; ma=ma->next) {
			spin_lock_bh(&ma->mca_lock);
			igmp6_group_queried(ma, max_delay);
			spin_unlock_bh(&ma->mca_lock);
		}
	} else {
		for (ma = idev->mc_list; ma; ma=ma->next) {
			if (!ipv6_addr_equal(group, &ma->mca_addr))
				continue;
			spin_lock_bh(&ma->mca_lock);
			if (ma->mca_flags & MAF_TIMER_RUNNING) {
				/* gsquery <- gsquery && mark */
				if (!mark)
					ma->mca_flags &= ~MAF_GSQUERY;
			} else {
				/* gsquery <- mark */
				if (mark)
					ma->mca_flags |= MAF_GSQUERY;
				else
					ma->mca_flags &= ~MAF_GSQUERY;
			}
			if (!(ma->mca_flags & MAF_GSQUERY) ||
			    mld_marksources(ma, ntohs(mlh2->mld2q_nsrcs), mlh2->mld2q_srcs))
				igmp6_group_queried(ma, max_delay);
			spin_unlock_bh(&ma->mca_lock);
			break;
		}
	}
	read_unlock_bh(&idev->lock);
	in6_dev_put(idev);

	return 0;
}