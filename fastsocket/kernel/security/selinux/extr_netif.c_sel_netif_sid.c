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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  sid; } ;
struct sel_netif {TYPE_1__ nsec; } ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sel_netif* sel_netif_find (int) ; 
 int sel_netif_sid_slow (int,int /*<<< orphan*/ *) ; 

int sel_netif_sid(int ifindex, u32 *sid)
{
	struct sel_netif *netif;

	rcu_read_lock();
	netif = sel_netif_find(ifindex);
	if (likely(netif != NULL)) {
		*sid = netif->nsec.sid;
		rcu_read_unlock();
		return 0;
	}
	rcu_read_unlock();

	return sel_netif_sid_slow(ifindex, sid);
}