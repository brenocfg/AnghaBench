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
struct bnx2x_mcast_ramrod_params {scalar_t__ mcast_list_len; struct bnx2x_mcast_obj* mcast_obj; } ;
struct bnx2x_mcast_obj {int /*<<< orphan*/  (* hdl_restore ) (struct bnx2x*,struct bnx2x_mcast_obj*,int /*<<< orphan*/ ,int*) ;} ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_mcast_cmd { ____Placeholder_bnx2x_mcast_cmd } bnx2x_mcast_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
#define  BNX2X_MCAST_CMD_ADD 130 
#define  BNX2X_MCAST_CMD_DEL 129 
#define  BNX2X_MCAST_CMD_RESTORE 128 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int EINVAL ; 
 int /*<<< orphan*/  bnx2x_mcast_hdl_add (struct bnx2x*,struct bnx2x_mcast_obj*,struct bnx2x_mcast_ramrod_params*,int*) ; 
 int /*<<< orphan*/  bnx2x_mcast_hdl_del (struct bnx2x*,struct bnx2x_mcast_obj*,struct bnx2x_mcast_ramrod_params*,int*) ; 
 int /*<<< orphan*/  stub1 (struct bnx2x*,struct bnx2x_mcast_obj*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline int bnx2x_mcast_handle_current_cmd(struct bnx2x *bp,
			struct bnx2x_mcast_ramrod_params *p,
			enum bnx2x_mcast_cmd cmd,
			int start_cnt)
{
	struct bnx2x_mcast_obj *o = p->mcast_obj;
	int cnt = start_cnt;

	DP(BNX2X_MSG_SP, "p->mcast_list_len=%d\n", p->mcast_list_len);

	switch (cmd) {
	case BNX2X_MCAST_CMD_ADD:
		bnx2x_mcast_hdl_add(bp, o, p, &cnt);
		break;

	case BNX2X_MCAST_CMD_DEL:
		bnx2x_mcast_hdl_del(bp, o, p, &cnt);
		break;

	case BNX2X_MCAST_CMD_RESTORE:
		o->hdl_restore(bp, o, 0, &cnt);
		break;

	default:
		BNX2X_ERR("Unknown command: %d\n", cmd);
		return -EINVAL;
	}

	/* The current command has been handled */
	p->mcast_list_len = 0;

	return cnt;
}