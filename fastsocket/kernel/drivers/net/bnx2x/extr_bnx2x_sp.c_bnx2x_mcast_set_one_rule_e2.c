#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union bnx2x_mcast_config_data {int bin; int /*<<< orphan*/  mac; } ;
typedef  int u8 ;
struct eth_multicast_rules_ramrod_data {TYPE_3__* rules; } ;
struct bnx2x_raw_obj {int func_id; scalar_t__ rdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  vec; } ;
struct TYPE_5__ {TYPE_1__ aprox_match; } ;
struct bnx2x_mcast_obj {int /*<<< orphan*/  engine_id; TYPE_2__ registry; struct bnx2x_raw_obj raw; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_mcast_cmd { ____Placeholder_bnx2x_mcast_cmd } bnx2x_mcast_cmd ;
struct TYPE_6__ {int cmd_general_data; int bin_id; int func_id; int /*<<< orphan*/  engine_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_VEC64_SET_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
#define  BNX2X_MCAST_CMD_ADD 130 
#define  BNX2X_MCAST_CMD_DEL 129 
#define  BNX2X_MCAST_CMD_RESTORE 128 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,char*,int) ; 
 int ETH_MULTICAST_RULES_CMD_IS_ADD ; 
 int bnx2x_mcast_bin_from_mac (int /*<<< orphan*/ ) ; 
 int bnx2x_mcast_clear_first_bin (struct bnx2x_mcast_obj*) ; 
 int bnx2x_mcast_get_rx_tx_flag (struct bnx2x_mcast_obj*) ; 

__attribute__((used)) static void bnx2x_mcast_set_one_rule_e2(struct bnx2x *bp,
					struct bnx2x_mcast_obj *o, int idx,
					union bnx2x_mcast_config_data *cfg_data,
					enum bnx2x_mcast_cmd cmd)
{
	struct bnx2x_raw_obj *r = &o->raw;
	struct eth_multicast_rules_ramrod_data *data =
		(struct eth_multicast_rules_ramrod_data *)(r->rdata);
	u8 func_id = r->func_id;
	u8 rx_tx_add_flag = bnx2x_mcast_get_rx_tx_flag(o);
	int bin;

	if ((cmd == BNX2X_MCAST_CMD_ADD) || (cmd == BNX2X_MCAST_CMD_RESTORE))
		rx_tx_add_flag |= ETH_MULTICAST_RULES_CMD_IS_ADD;

	data->rules[idx].cmd_general_data |= rx_tx_add_flag;

	/* Get a bin and update a bins' vector */
	switch (cmd) {
	case BNX2X_MCAST_CMD_ADD:
		bin = bnx2x_mcast_bin_from_mac(cfg_data->mac);
		BIT_VEC64_SET_BIT(o->registry.aprox_match.vec, bin);
		break;

	case BNX2X_MCAST_CMD_DEL:
		/* If there were no more bins to clear
		 * (bnx2x_mcast_clear_first_bin() returns -1) then we would
		 * clear any (0xff) bin.
		 * See bnx2x_mcast_validate_e2() for explanation when it may
		 * happen.
		 */
		bin = bnx2x_mcast_clear_first_bin(o);
		break;

	case BNX2X_MCAST_CMD_RESTORE:
		bin = cfg_data->bin;
		break;

	default:
		BNX2X_ERR("Unknown command: %d\n", cmd);
		return;
	}

	DP(BNX2X_MSG_SP, "%s bin %d\n",
			 ((rx_tx_add_flag & ETH_MULTICAST_RULES_CMD_IS_ADD) ?
			 "Setting"  : "Clearing"), bin);

	data->rules[idx].bin_id    = (u8)bin;
	data->rules[idx].func_id   = func_id;
	data->rules[idx].engine_id = o->engine_id;
}