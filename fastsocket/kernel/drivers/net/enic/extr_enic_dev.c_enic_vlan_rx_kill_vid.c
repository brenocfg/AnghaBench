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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct enic {int /*<<< orphan*/  devcmd_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  enic_del_vlan (struct enic*,int /*<<< orphan*/ ) ; 
 struct enic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void enic_vlan_rx_kill_vid(struct net_device *netdev, u16 vid)
{
	struct enic *enic = netdev_priv(netdev);

	spin_lock(&enic->devcmd_lock);
	enic_del_vlan(enic, vid);
	spin_unlock(&enic->devcmd_lock);
}