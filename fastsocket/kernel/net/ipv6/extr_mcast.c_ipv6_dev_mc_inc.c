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
struct net_device {int dummy; } ;
struct inet6_dev {int /*<<< orphan*/  lock; struct ifmcaddr6* mc_list; scalar_t__ dead; } ;
struct in6_addr {int dummy; } ;
struct ifmcaddr6 {int mca_users; size_t mca_sfmode; int* mca_sfcount; int /*<<< orphan*/  mca_addr; struct ifmcaddr6* next; int /*<<< orphan*/  mca_flags; int /*<<< orphan*/  mca_lock; int /*<<< orphan*/  mca_refcnt; int /*<<< orphan*/  mca_tstamp; int /*<<< orphan*/  mca_cstamp; struct inet6_dev* idev; int /*<<< orphan*/  mca_timer; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IPV6_ADDR_MC_SCOPE (int /*<<< orphan*/ *) ; 
 scalar_t__ IPV6_ADDR_SCOPE_LINKLOCAL ; 
 int /*<<< orphan*/  MAF_NOREPORT ; 
 size_t MCAST_EXCLUDE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  igmp6_group_added (struct ifmcaddr6*) ; 
 int /*<<< orphan*/  igmp6_timer_handler ; 
 struct inet6_dev* in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 int /*<<< orphan*/  ip6_mc_add_src (struct inet6_dev*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,struct in6_addr const*) ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,struct in6_addr const*) ; 
 scalar_t__ ipv6_addr_is_ll_all_nodes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 struct ifmcaddr6* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ma_put (struct ifmcaddr6*) ; 
 int /*<<< orphan*/  mld_del_delrec (struct inet6_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int ipv6_dev_mc_inc(struct net_device *dev, const struct in6_addr *addr)
{
	struct ifmcaddr6 *mc;
	struct inet6_dev *idev;

	idev = in6_dev_get(dev);

	if (idev == NULL)
		return -EINVAL;

	write_lock_bh(&idev->lock);
	if (idev->dead) {
		write_unlock_bh(&idev->lock);
		in6_dev_put(idev);
		return -ENODEV;
	}

	for (mc = idev->mc_list; mc; mc = mc->next) {
		if (ipv6_addr_equal(&mc->mca_addr, addr)) {
			mc->mca_users++;
			write_unlock_bh(&idev->lock);
			ip6_mc_add_src(idev, &mc->mca_addr, MCAST_EXCLUDE, 0,
				NULL, 0);
			in6_dev_put(idev);
			return 0;
		}
	}

	/*
	 *	not found: create a new one.
	 */

	mc = kzalloc(sizeof(struct ifmcaddr6), GFP_ATOMIC);

	if (mc == NULL) {
		write_unlock_bh(&idev->lock);
		in6_dev_put(idev);
		return -ENOMEM;
	}

	setup_timer(&mc->mca_timer, igmp6_timer_handler, (unsigned long)mc);

	ipv6_addr_copy(&mc->mca_addr, addr);
	mc->idev = idev;
	mc->mca_users = 1;
	/* mca_stamp should be updated upon changes */
	mc->mca_cstamp = mc->mca_tstamp = jiffies;
	atomic_set(&mc->mca_refcnt, 2);
	spin_lock_init(&mc->mca_lock);

	/* initial mode is (EX, empty) */
	mc->mca_sfmode = MCAST_EXCLUDE;
	mc->mca_sfcount[MCAST_EXCLUDE] = 1;

	if (ipv6_addr_is_ll_all_nodes(&mc->mca_addr) ||
	    IPV6_ADDR_MC_SCOPE(&mc->mca_addr) < IPV6_ADDR_SCOPE_LINKLOCAL)
		mc->mca_flags |= MAF_NOREPORT;

	mc->next = idev->mc_list;
	idev->mc_list = mc;
	write_unlock_bh(&idev->lock);

	mld_del_delrec(idev, &mc->mca_addr);
	igmp6_group_added(mc);
	ma_put(mc);
	return 0;
}