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
struct TYPE_3__ {int rmx_locks; scalar_t__ rmx_mtu; } ;
struct rtentry {TYPE_1__ rt_rmx; struct ifnet* rt_ifp; } ;
struct radix_node {int dummy; } ;
struct ifnet {scalar_t__ if_mtu; } ;
struct TYPE_4__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ CLAT46_HDR_EXPANSION_OVERHD ; 
 scalar_t__ IN6_LINKMTU (struct ifnet*) ; 
 scalar_t__ INTF_ADJUST_MTU_FOR_CLAT46 (struct ifnet*) ; 
 int RTV_MTU ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 TYPE_2__* rt_key (struct rtentry*) ; 

__attribute__((used)) static int
if_rtmtu(struct radix_node *rn, void *arg)
{
	struct rtentry *rt = (struct rtentry *)rn;
	struct ifnet *ifp = arg;

	RT_LOCK(rt);
	if (rt->rt_ifp == ifp) {
		/*
		 * Update the MTU of this entry only if the MTU
		 * has not been locked (RTV_MTU is not set) and
		 * if it was non-zero to begin with.
		 */
		if (!(rt->rt_rmx.rmx_locks & RTV_MTU) && rt->rt_rmx.rmx_mtu) {
			rt->rt_rmx.rmx_mtu = ifp->if_mtu;
			if (rt_key(rt)->sa_family == AF_INET &&
			    INTF_ADJUST_MTU_FOR_CLAT46(ifp)) {
				rt->rt_rmx.rmx_mtu = IN6_LINKMTU(ifp);
				/* Further adjust the size for CLAT46 expansion */
				rt->rt_rmx.rmx_mtu -= CLAT46_HDR_EXPANSION_OVERHD;
			}
		}
	}
	RT_UNLOCK(rt);

	return (0);
}