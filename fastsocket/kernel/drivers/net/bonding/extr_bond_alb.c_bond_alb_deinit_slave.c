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
struct slave {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * next_rx_slave; scalar_t__ rlb_enabled; } ;
struct bonding {int slave_cnt; TYPE_1__ alb_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  alb_change_hw_addr_on_detach (struct bonding*,struct slave*) ; 
 int /*<<< orphan*/  rlb_clear_slave (struct bonding*,struct slave*) ; 
 int /*<<< orphan*/  tlb_clear_slave (struct bonding*,struct slave*,int /*<<< orphan*/ ) ; 

void bond_alb_deinit_slave(struct bonding *bond, struct slave *slave)
{
	if (bond->slave_cnt > 1) {
		alb_change_hw_addr_on_detach(bond, slave);
	}

	tlb_clear_slave(bond, slave, 0);

	if (bond->alb_info.rlb_enabled) {
		bond->alb_info.next_rx_slave = NULL;
		rlb_clear_slave(bond, slave);
	}
}