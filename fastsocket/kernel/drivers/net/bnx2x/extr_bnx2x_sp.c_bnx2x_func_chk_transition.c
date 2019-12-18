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
struct bnx2x_func_state_params {int cmd; scalar_t__ ramrod_flags; } ;
struct bnx2x_func_sp_obj {int state; int next_state; scalar_t__ pending; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_func_state { ____Placeholder_bnx2x_func_state } bnx2x_func_state ;
typedef  enum bnx2x_func_cmd { ____Placeholder_bnx2x_func_cmd } bnx2x_func_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
 int BNX2X_F_CMD_AFEX_UPDATE ; 
 int BNX2X_F_CMD_AFEX_VIFLISTS ; 
 int BNX2X_F_CMD_HW_INIT ; 
 int BNX2X_F_CMD_HW_RESET ; 
 int BNX2X_F_CMD_START ; 
 int BNX2X_F_CMD_STOP ; 
 int BNX2X_F_CMD_SWITCH_UPDATE ; 
 int BNX2X_F_CMD_TX_START ; 
 int BNX2X_F_CMD_TX_STOP ; 
#define  BNX2X_F_STATE_INITIALIZED 131 
 int BNX2X_F_STATE_MAX ; 
#define  BNX2X_F_STATE_RESET 130 
#define  BNX2X_F_STATE_STARTED 129 
#define  BNX2X_F_STATE_TX_STOPPED 128 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int EBUSY ; 
 int EINVAL ; 
 int RAMROD_DRV_CLR_ONLY ; 
 scalar_t__ test_bit (int,scalar_t__*) ; 

__attribute__((used)) static int bnx2x_func_chk_transition(struct bnx2x *bp,
				     struct bnx2x_func_sp_obj *o,
				     struct bnx2x_func_state_params *params)
{
	enum bnx2x_func_state state = o->state, next_state = BNX2X_F_STATE_MAX;
	enum bnx2x_func_cmd cmd = params->cmd;

	/* Forget all pending for completion commands if a driver only state
	 * transition has been requested.
	 */
	if (test_bit(RAMROD_DRV_CLR_ONLY, &params->ramrod_flags)) {
		o->pending = 0;
		o->next_state = BNX2X_F_STATE_MAX;
	}

	/* Don't allow a next state transition if we are in the middle of
	 * the previous one.
	 */
	if (o->pending)
		return -EBUSY;

	switch (state) {
	case BNX2X_F_STATE_RESET:
		if (cmd == BNX2X_F_CMD_HW_INIT)
			next_state = BNX2X_F_STATE_INITIALIZED;

		break;
	case BNX2X_F_STATE_INITIALIZED:
		if (cmd == BNX2X_F_CMD_START)
			next_state = BNX2X_F_STATE_STARTED;

		else if (cmd == BNX2X_F_CMD_HW_RESET)
			next_state = BNX2X_F_STATE_RESET;

		break;
	case BNX2X_F_STATE_STARTED:
		if (cmd == BNX2X_F_CMD_STOP)
			next_state = BNX2X_F_STATE_INITIALIZED;
		/* afex ramrods can be sent only in started mode, and only
		 * if not pending for function_stop ramrod completion
		 * for these events - next state remained STARTED.
		 */
		else if ((cmd == BNX2X_F_CMD_AFEX_UPDATE) &&
			 (!test_bit(BNX2X_F_CMD_STOP, &o->pending)))
			next_state = BNX2X_F_STATE_STARTED;

		else if ((cmd == BNX2X_F_CMD_AFEX_VIFLISTS) &&
			 (!test_bit(BNX2X_F_CMD_STOP, &o->pending)))
			next_state = BNX2X_F_STATE_STARTED;

		/* Switch_update ramrod can be sent in either started or
		 * tx_stopped state, and it doesn't change the state.
		 */
		else if ((cmd == BNX2X_F_CMD_SWITCH_UPDATE) &&
			 (!test_bit(BNX2X_F_CMD_STOP, &o->pending)))
			next_state = BNX2X_F_STATE_STARTED;

		else if (cmd == BNX2X_F_CMD_TX_STOP)
			next_state = BNX2X_F_STATE_TX_STOPPED;

		break;
	case BNX2X_F_STATE_TX_STOPPED:
		if ((cmd == BNX2X_F_CMD_SWITCH_UPDATE) &&
		    (!test_bit(BNX2X_F_CMD_STOP, &o->pending)))
			next_state = BNX2X_F_STATE_TX_STOPPED;

		else if (cmd == BNX2X_F_CMD_TX_START)
			next_state = BNX2X_F_STATE_STARTED;

		break;
	default:
		BNX2X_ERR("Unknown state: %d\n", state);
	}

	/* Transition is assured */
	if (next_state != BNX2X_F_STATE_MAX) {
		DP(BNX2X_MSG_SP, "Good function state transition: %d(%d)->%d\n",
				 state, cmd, next_state);
		o->next_state = next_state;
		return 0;
	}

	DP(BNX2X_MSG_SP, "Bad function state transition request: %d %d\n",
			 state, cmd);

	return -EINVAL;
}