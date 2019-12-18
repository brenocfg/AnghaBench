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
struct bnx2x_queue_state_params {int /*<<< orphan*/  ramrod_flags; int /*<<< orphan*/  cmd; int /*<<< orphan*/ * q_obj; int /*<<< orphan*/ * member_0; } ;
struct bnx2x {TYPE_1__* sp_objs; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  q_obj; } ;

/* Variables and functions */
 int BNX2X_MSG_ETHTOOL ; 
 int BNX2X_MSG_NVM ; 
 int /*<<< orphan*/  BNX2X_Q_CMD_EMPTY ; 
 int /*<<< orphan*/  DP (int,char*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bnx2x_queue_state_change (struct bnx2x*,struct bnx2x_queue_state_params*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_test_intr(struct bnx2x *bp)
{
	struct bnx2x_queue_state_params params = {NULL};

	if (!netif_running(bp->dev)) {
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "cannot access eeprom when the interface is down\n");
		return -ENODEV;
	}

	params.q_obj = &bp->sp_objs->q_obj;
	params.cmd = BNX2X_Q_CMD_EMPTY;

	__set_bit(RAMROD_COMP_WAIT, &params.ramrod_flags);

	return bnx2x_queue_state_change(bp, &params);
}