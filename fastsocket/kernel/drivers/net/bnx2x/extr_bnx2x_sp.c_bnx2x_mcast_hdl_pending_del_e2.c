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
struct TYPE_2__ {scalar_t__ macs_num; } ;
struct bnx2x_pending_mcast_cmd {int done; TYPE_1__ data; int /*<<< orphan*/  type; } ;
struct bnx2x_mcast_obj {int max_cmd_len; int /*<<< orphan*/  (* set_one_rule ) (struct bnx2x*,struct bnx2x_mcast_obj*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (struct bnx2x*,struct bnx2x_mcast_obj*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bnx2x_mcast_hdl_pending_del_e2(struct bnx2x *bp,
	struct bnx2x_mcast_obj *o, struct bnx2x_pending_mcast_cmd *cmd_pos,
	int *line_idx)
{
	int cnt = *line_idx;

	while (cmd_pos->data.macs_num) {
		o->set_one_rule(bp, o, cnt, NULL, cmd_pos->type);

		cnt++;

		cmd_pos->data.macs_num--;

		  DP(BNX2X_MSG_SP, "Deleting MAC. %d left,cnt is %d\n",
				   cmd_pos->data.macs_num, cnt);

		/* Break if we reached the maximum
		 * number of rules.
		 */
		if (cnt >= o->max_cmd_len)
			break;
	}

	*line_idx = cnt;

	/* If we cleared all bins - we are done */
	if (!cmd_pos->data.macs_num)
		cmd_pos->done = true;
}