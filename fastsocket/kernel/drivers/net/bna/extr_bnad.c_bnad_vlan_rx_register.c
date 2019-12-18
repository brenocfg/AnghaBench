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
struct vlan_group {int dummy; } ;
struct net_device {int dummy; } ;
struct bnad {int /*<<< orphan*/  conf_mutex; struct vlan_group* vlan_grp; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bnad* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
bnad_vlan_rx_register(struct net_device *netdev,
				  struct vlan_group *vlan_grp)
{
	struct bnad *bnad = netdev_priv(netdev);

	mutex_lock(&bnad->conf_mutex);
	bnad->vlan_grp = vlan_grp;
	mutex_unlock(&bnad->conf_mutex);
}