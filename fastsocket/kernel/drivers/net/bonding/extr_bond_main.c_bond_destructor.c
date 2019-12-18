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
struct net_device {int dummy; } ;
struct bonding {scalar_t__ wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct bonding* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void bond_destructor(struct net_device *bond_dev)
{
	struct bonding *bond = netdev_priv(bond_dev);
	if (bond->wq)
		destroy_workqueue(bond->wq);
	free_netdev(bond_dev);
}