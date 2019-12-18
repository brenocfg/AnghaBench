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
struct bonding {int /*<<< orphan*/  bond_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  bond_remove_proc_entry (struct bonding*) ; 
 int /*<<< orphan*/  bond_work_cancel_all (struct bonding*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct bonding* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void bond_deinit(struct net_device *bond_dev)
{
	struct bonding *bond = netdev_priv(bond_dev);

	list_del(&bond->bond_list);

	bond_work_cancel_all(bond);

	bond_remove_proc_entry(bond);
}