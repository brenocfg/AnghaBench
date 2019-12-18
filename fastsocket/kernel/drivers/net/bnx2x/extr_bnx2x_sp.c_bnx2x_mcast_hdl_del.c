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
struct bnx2x_mcast_ramrod_params {int mcast_list_len; } ;
struct bnx2x_mcast_obj {int /*<<< orphan*/  (* set_one_rule ) (struct bnx2x*,struct bnx2x_mcast_obj*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MCAST_CMD_DEL ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct bnx2x*,struct bnx2x_mcast_obj*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bnx2x_mcast_hdl_del(struct bnx2x *bp,
	struct bnx2x_mcast_obj *o, struct bnx2x_mcast_ramrod_params *p,
	int *line_idx)
{
	int cnt = *line_idx, i;

	for (i = 0; i < p->mcast_list_len; i++) {
		o->set_one_rule(bp, o, cnt, NULL, BNX2X_MCAST_CMD_DEL);

		cnt++;

		DP(BNX2X_MSG_SP, "Deleting MAC. %d left\n",
				 p->mcast_list_len - i - 1);
	}

	*line_idx = cnt;
}