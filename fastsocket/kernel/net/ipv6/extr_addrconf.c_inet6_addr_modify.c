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
typedef  int u8 ;
typedef  void* u32 ;
struct inet6_ifaddr {int flags; TYPE_1__* idev; int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  addr; int /*<<< orphan*/  lock; void* prefered_lft; void* valid_lft; int /*<<< orphan*/  tstamp; } ;
typedef  scalar_t__ clock_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long HZ ; 
 int IFA_F_DEPRECATED ; 
 int IFA_F_HOMEADDRESS ; 
 int IFA_F_NODAD ; 
 int IFA_F_PERMANENT ; 
 int IFA_F_TENTATIVE ; 
 void* RTF_EXPIRES ; 
 scalar_t__ addrconf_finite_timeout (unsigned long) ; 
 int /*<<< orphan*/  addrconf_prefix_route (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*) ; 
 unsigned long addrconf_timeout_fixup (void*,unsigned long) ; 
 int /*<<< orphan*/  addrconf_verify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_ifa_notify (int /*<<< orphan*/ ,struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ jiffies_to_clock_t (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int inet6_addr_modify(struct inet6_ifaddr *ifp, u8 ifa_flags,
			     u32 prefered_lft, u32 valid_lft)
{
	u32 flags;
	clock_t expires;
	unsigned long timeout;

	if (!valid_lft || (prefered_lft > valid_lft))
		return -EINVAL;

	timeout = addrconf_timeout_fixup(valid_lft, HZ);
	if (addrconf_finite_timeout(timeout)) {
		expires = jiffies_to_clock_t(timeout * HZ);
		valid_lft = timeout;
		flags = RTF_EXPIRES;
	} else {
		expires = 0;
		flags = 0;
		ifa_flags |= IFA_F_PERMANENT;
	}

	timeout = addrconf_timeout_fixup(prefered_lft, HZ);
	if (addrconf_finite_timeout(timeout)) {
		if (timeout == 0)
			ifa_flags |= IFA_F_DEPRECATED;
		prefered_lft = timeout;
	}

	spin_lock_bh(&ifp->lock);
	ifp->flags = (ifp->flags & ~(IFA_F_DEPRECATED | IFA_F_PERMANENT | IFA_F_NODAD | IFA_F_HOMEADDRESS)) | ifa_flags;
	ifp->tstamp = jiffies;
	ifp->valid_lft = valid_lft;
	ifp->prefered_lft = prefered_lft;

	spin_unlock_bh(&ifp->lock);
	if (!(ifp->flags&IFA_F_TENTATIVE))
		ipv6_ifa_notify(0, ifp);

	addrconf_prefix_route(&ifp->addr, ifp->prefix_len, ifp->idev->dev,
			      expires, flags);
	addrconf_verify(0);

	return 0;
}