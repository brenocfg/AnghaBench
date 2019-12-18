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
struct inet6_ifaddr {scalar_t__ dead; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ INET6_IFADDR_STATE_DAD ; 
 scalar_t__ INET6_IFADDR_STATE_POSTDAD ; 
 int /*<<< orphan*/  ifa_state_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int addrconf_dad_end(struct inet6_ifaddr *ifp)
{
	int err = -ENOENT;

	spin_lock(&ifa_state_lock);
	if (ifp->dead == INET6_IFADDR_STATE_DAD) {
		ifp->dead = INET6_IFADDR_STATE_POSTDAD;
		err = 0;
	}
	spin_unlock(&ifa_state_lock);

	return err;
}