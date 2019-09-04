#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ rmx_mtu; } ;
struct rtentry {TYPE_1__ rt_rmx; TYPE_3__* rt_ifp; } ;
struct TYPE_7__ {int if_mtu; } ;
struct TYPE_6__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ CLAT46_HDR_EXPANSION_OVERHD ; 
 int IN6_LINKMTU (TYPE_3__*) ; 
 scalar_t__ INTF_ADJUST_MTU_FOR_CLAT46 (TYPE_3__*) ; 
 unsigned int MIN (scalar_t__,int) ; 
 int /*<<< orphan*/  RT_LOCK_ASSERT_HELD (struct rtentry*) ; 
 TYPE_2__* rt_key (struct rtentry*) ; 

__attribute__((used)) static inline unsigned int
tcp_maxmtu(struct rtentry *rt)
{
	unsigned int maxmtu;
	int interface_mtu = 0;

	RT_LOCK_ASSERT_HELD(rt);
	interface_mtu = rt->rt_ifp->if_mtu;

	if (rt_key(rt)->sa_family == AF_INET &&
	    INTF_ADJUST_MTU_FOR_CLAT46(rt->rt_ifp)) {
		interface_mtu = IN6_LINKMTU(rt->rt_ifp);
		/* Further adjust the size for CLAT46 expansion */
		interface_mtu -= CLAT46_HDR_EXPANSION_OVERHD;
	}

	if (rt->rt_rmx.rmx_mtu == 0)
		maxmtu = interface_mtu;
	else
		maxmtu = MIN(rt->rt_rmx.rmx_mtu, interface_mtu);

	return (maxmtu);
}