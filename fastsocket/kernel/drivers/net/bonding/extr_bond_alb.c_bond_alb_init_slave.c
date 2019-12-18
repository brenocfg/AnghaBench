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
struct slave {int /*<<< orphan*/  perm_hwaddr; } ;
struct TYPE_2__ {int rlb_rebalance; scalar_t__ rlb_enabled; int /*<<< orphan*/  tx_rebalance_counter; } ;
struct bonding {TYPE_1__ alb_info; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOND_TLB_REBALANCE_TICKS ; 
 int alb_handle_addr_collision_on_attach (struct bonding*,struct slave*) ; 
 int alb_set_slave_mac_addr (struct slave*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlb_init_slave (struct slave*) ; 

int bond_alb_init_slave(struct bonding *bond, struct slave *slave)
{
	int res;

	res = alb_set_slave_mac_addr(slave, slave->perm_hwaddr);
	if (res) {
		return res;
	}

	/* caller must hold the bond lock for write since the mac addresses
	 * are compared and may be swapped.
	 */
	read_lock(&bond->lock);

	res = alb_handle_addr_collision_on_attach(bond, slave);

	read_unlock(&bond->lock);

	if (res) {
		return res;
	}

	tlb_init_slave(slave);

	/* order a rebalance ASAP */
	bond->alb_info.tx_rebalance_counter = BOND_TLB_REBALANCE_TICKS;

	if (bond->alb_info.rlb_enabled) {
		bond->alb_info.rlb_rebalance = 1;
	}

	return 0;
}