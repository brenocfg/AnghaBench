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
union bnx2x_mcast_config_data {scalar_t__ bin; int /*<<< orphan*/ * member_0; } ;
typedef  scalar_t__ u8 ;
struct bnx2x_mcast_obj {int max_cmd_len; int /*<<< orphan*/  (* set_one_rule ) (struct bnx2x*,struct bnx2x_mcast_obj*,int,union bnx2x_mcast_config_data*,int /*<<< orphan*/ ) ;} ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MCAST_CMD_RESTORE ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int bnx2x_mcast_get_next_bin (struct bnx2x_mcast_obj*,int) ; 
 int /*<<< orphan*/  stub1 (struct bnx2x*,struct bnx2x_mcast_obj*,int,union bnx2x_mcast_config_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int bnx2x_mcast_handle_restore_cmd_e2(
	struct bnx2x *bp, struct bnx2x_mcast_obj *o , int start_bin,
	int *rdata_idx)
{
	int cur_bin, cnt = *rdata_idx;
	union bnx2x_mcast_config_data cfg_data = {NULL};

	/* go through the registry and configure the bins from it */
	for (cur_bin = bnx2x_mcast_get_next_bin(o, start_bin); cur_bin >= 0;
	    cur_bin = bnx2x_mcast_get_next_bin(o, cur_bin + 1)) {

		cfg_data.bin = (u8)cur_bin;
		o->set_one_rule(bp, o, cnt, &cfg_data,
				BNX2X_MCAST_CMD_RESTORE);

		cnt++;

		DP(BNX2X_MSG_SP, "About to configure a bin %d\n", cur_bin);

		/* Break if we reached the maximum number
		 * of rules.
		 */
		if (cnt >= o->max_cmd_len)
			break;
	}

	*rdata_idx = cnt;

	return cur_bin;
}