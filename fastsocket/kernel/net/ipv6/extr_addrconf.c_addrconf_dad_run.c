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
struct inet6_ifaddr {int flags; scalar_t__ dead; int /*<<< orphan*/  lock; struct inet6_ifaddr* if_next; } ;
struct inet6_dev {int /*<<< orphan*/  lock; struct inet6_ifaddr* addr_list; } ;

/* Variables and functions */
 int IFA_F_TENTATIVE ; 
 scalar_t__ INET6_IFADDR_STATE_DAD ; 
 int /*<<< orphan*/  addrconf_dad_kick (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void addrconf_dad_run(struct inet6_dev *idev) {
	struct inet6_ifaddr *ifp;

	read_lock_bh(&idev->lock);
	for (ifp = idev->addr_list; ifp; ifp = ifp->if_next) {
		spin_lock_bh(&ifp->lock);
		if (ifp->flags & IFA_F_TENTATIVE &&
		    ifp->dead == INET6_IFADDR_STATE_DAD)
			addrconf_dad_kick(ifp);
		spin_unlock_bh(&ifp->lock);
	}
	read_unlock_bh(&idev->lock);
}