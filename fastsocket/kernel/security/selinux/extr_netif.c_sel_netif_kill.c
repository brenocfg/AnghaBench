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
struct sel_netif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sel_netif_destroy (struct sel_netif*) ; 
 struct sel_netif* sel_netif_find (int) ; 
 int /*<<< orphan*/  sel_netif_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sel_netif_kill(int ifindex)
{
	struct sel_netif *netif;

	rcu_read_lock();
	spin_lock_bh(&sel_netif_lock);
	netif = sel_netif_find(ifindex);
	if (netif)
		sel_netif_destroy(netif);
	spin_unlock_bh(&sel_netif_lock);
	rcu_read_unlock();
}