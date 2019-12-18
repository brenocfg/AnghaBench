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
struct slave {TYPE_2__* dev; } ;
struct TYPE_3__ {scalar_t__ rlb_enabled; } ;
struct bonding {TYPE_1__ alb_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 scalar_t__ SLAVE_IS_OK (struct slave*) ; 
 int /*<<< orphan*/  alb_send_learning_packets (struct slave*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rlb_req_update_slave_clients (struct bonding*,struct slave*) ; 
 int /*<<< orphan*/  rlb_teach_disabled_mac_on_primary (struct bonding*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alb_fasten_mac_swap(struct bonding *bond, struct slave *slave1,
				struct slave *slave2)
{
	int slaves_state_differ = (SLAVE_IS_OK(slave1) != SLAVE_IS_OK(slave2));
	struct slave *disabled_slave = NULL;

	ASSERT_RTNL();

	/* fasten the change in the switch */
	if (SLAVE_IS_OK(slave1)) {
		alb_send_learning_packets(slave1, slave1->dev->dev_addr);
		if (bond->alb_info.rlb_enabled) {
			/* inform the clients that the mac address
			 * has changed
			 */
			rlb_req_update_slave_clients(bond, slave1);
		}
	} else {
		disabled_slave = slave1;
	}

	if (SLAVE_IS_OK(slave2)) {
		alb_send_learning_packets(slave2, slave2->dev->dev_addr);
		if (bond->alb_info.rlb_enabled) {
			/* inform the clients that the mac address
			 * has changed
			 */
			rlb_req_update_slave_clients(bond, slave2);
		}
	} else {
		disabled_slave = slave2;
	}

	if (bond->alb_info.rlb_enabled && slaves_state_differ) {
		/* A disabled slave was assigned an active mac addr */
		rlb_teach_disabled_mac_on_primary(bond,
						  disabled_slave->dev->dev_addr);
	}
}