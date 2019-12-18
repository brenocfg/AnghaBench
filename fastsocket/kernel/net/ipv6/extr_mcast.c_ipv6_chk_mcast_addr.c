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
struct ip6_sf_list {scalar_t__* sf_count; int /*<<< orphan*/  sf_addr; struct ip6_sf_list* sf_next; } ;
struct inet6_dev {int /*<<< orphan*/  lock; struct ifmcaddr6* mc_list; } ;
struct in6_addr {int dummy; } ;
struct ifmcaddr6 {scalar_t__* mca_sfcount; int /*<<< orphan*/  mca_lock; struct ip6_sf_list* mca_sources; int /*<<< orphan*/  mca_addr; struct ifmcaddr6* next; } ;

/* Variables and functions */
 size_t MCAST_EXCLUDE ; 
 size_t MCAST_INCLUDE ; 
 struct inet6_dev* in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 int /*<<< orphan*/  ipv6_addr_any (struct in6_addr const*) ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,struct in6_addr const*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int ipv6_chk_mcast_addr(struct net_device *dev, const struct in6_addr *group,
			const struct in6_addr *src_addr)
{
	struct inet6_dev *idev;
	struct ifmcaddr6 *mc;
	int rv = 0;

	idev = in6_dev_get(dev);
	if (idev) {
		read_lock_bh(&idev->lock);
		for (mc = idev->mc_list; mc; mc=mc->next) {
			if (ipv6_addr_equal(&mc->mca_addr, group))
				break;
		}
		if (mc) {
			if (src_addr && !ipv6_addr_any(src_addr)) {
				struct ip6_sf_list *psf;

				spin_lock_bh(&mc->mca_lock);
				for (psf=mc->mca_sources;psf;psf=psf->sf_next) {
					if (ipv6_addr_equal(&psf->sf_addr, src_addr))
						break;
				}
				if (psf)
					rv = psf->sf_count[MCAST_INCLUDE] ||
						psf->sf_count[MCAST_EXCLUDE] !=
						mc->mca_sfcount[MCAST_EXCLUDE];
				else
					rv = mc->mca_sfcount[MCAST_EXCLUDE] !=0;
				spin_unlock_bh(&mc->mca_lock);
			} else
				rv = 1; /* don't filter unspecified source */
		}
		read_unlock_bh(&idev->lock);
		in6_dev_put(idev);
	}
	return rv;
}