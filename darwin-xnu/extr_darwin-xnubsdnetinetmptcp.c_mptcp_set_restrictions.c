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
typedef  size_t uint32_t ;
struct socket {int so_restrictions; } ;
struct mptses {size_t mpte_itfinfo_size; struct mpt_itf_info* mpte_itfinfo; } ;
struct mpt_itf_info {size_t ifindex; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 scalar_t__ IFNET_IS_CELLULAR (struct ifnet*) ; 
 scalar_t__ IFNET_IS_EXPENSIVE (struct ifnet*) ; 
 size_t IFSCOPE_NONE ; 
 int SO_RESTRICT_DENY_CELLULAR ; 
 int SO_RESTRICT_DENY_EXPENSIVE ; 
 struct ifnet** ifindex2ifnet ; 
 int /*<<< orphan*/  ifnet_head_done () ; 
 int /*<<< orphan*/  ifnet_head_lock_shared () ; 
 struct mptses* mpsotompte (struct socket*) ; 
 int /*<<< orphan*/  mpte_lock_assert_held (struct mptses*) ; 

void
mptcp_set_restrictions(struct socket *mp_so)
{
	struct mptses *mpte = mpsotompte(mp_so);
	uint32_t i;

	mpte_lock_assert_held(mpte);

	ifnet_head_lock_shared();

	for (i = 0; i < mpte->mpte_itfinfo_size; i++) {
		struct mpt_itf_info *info = &mpte->mpte_itfinfo[i];
		uint32_t ifindex = info->ifindex;
		struct ifnet *ifp;

		if (ifindex == IFSCOPE_NONE)
			continue;

		ifp = ifindex2ifnet[ifindex];
		if (ifp == NULL)
			continue;

		if (IFNET_IS_EXPENSIVE(ifp) &&
		    (mp_so->so_restrictions & SO_RESTRICT_DENY_EXPENSIVE))
			info->ifindex = IFSCOPE_NONE;

		if (IFNET_IS_CELLULAR(ifp) &&
		    (mp_so->so_restrictions & SO_RESTRICT_DENY_CELLULAR))
			info->ifindex = IFSCOPE_NONE;
	}

	ifnet_head_done();
}