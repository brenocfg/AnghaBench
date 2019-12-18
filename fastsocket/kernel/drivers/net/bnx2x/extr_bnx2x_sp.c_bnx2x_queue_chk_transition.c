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
typedef  int u8 ;
struct bnx2x_queue_update_params {int /*<<< orphan*/  update_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__ setup; struct bnx2x_queue_update_params update; } ;
struct bnx2x_queue_state_params {int cmd; TYPE_2__ params; int /*<<< orphan*/  ramrod_flags; } ;
struct bnx2x_queue_sp_obj {int state; int num_tx_only; int pending; int next_state; int next_tx_only; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_queue_cmd { ____Placeholder_bnx2x_queue_cmd } bnx2x_queue_cmd ;
typedef  enum bnx2x_q_state { ____Placeholder_bnx2x_q_state } bnx2x_q_state ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int BNX2X_Q_CMD_ACTIVATE ; 
 int BNX2X_Q_CMD_CFC_DEL ; 
 int BNX2X_Q_CMD_DEACTIVATE ; 
 int BNX2X_Q_CMD_EMPTY ; 
 int BNX2X_Q_CMD_HALT ; 
 int BNX2X_Q_CMD_INIT ; 
 int BNX2X_Q_CMD_SETUP ; 
 int BNX2X_Q_CMD_SETUP_TX_ONLY ; 
 int BNX2X_Q_CMD_TERMINATE ; 
 int BNX2X_Q_CMD_UPDATE ; 
 int BNX2X_Q_CMD_UPDATE_TPA ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_ACTIVE ; 
#define  BNX2X_Q_STATE_ACTIVE 135 
#define  BNX2X_Q_STATE_INACTIVE 134 
#define  BNX2X_Q_STATE_INITIALIZED 133 
 int BNX2X_Q_STATE_MAX ; 
#define  BNX2X_Q_STATE_MCOS_TERMINATED 132 
#define  BNX2X_Q_STATE_MULTI_COS 131 
#define  BNX2X_Q_STATE_RESET 130 
#define  BNX2X_Q_STATE_STOPPED 129 
#define  BNX2X_Q_STATE_TERMINATED 128 
 int /*<<< orphan*/  BNX2X_Q_UPDATE_ACTIVATE ; 
 int /*<<< orphan*/  BNX2X_Q_UPDATE_ACTIVATE_CHNG ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  RAMROD_DRV_CLR_ONLY ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2x_queue_chk_transition(struct bnx2x *bp,
				      struct bnx2x_queue_sp_obj *o,
				      struct bnx2x_queue_state_params *params)
{
	enum bnx2x_q_state state = o->state, next_state = BNX2X_Q_STATE_MAX;
	enum bnx2x_queue_cmd cmd = params->cmd;
	struct bnx2x_queue_update_params *update_params =
		 &params->params.update;
	u8 next_tx_only = o->num_tx_only;

	/* Forget all pending for completion commands if a driver only state
	 * transition has been requested.
	 */
	if (test_bit(RAMROD_DRV_CLR_ONLY, &params->ramrod_flags)) {
		o->pending = 0;
		o->next_state = BNX2X_Q_STATE_MAX;
	}

	/* Don't allow a next state transition if we are in the middle of
	 * the previous one.
	 */
	if (o->pending) {
		BNX2X_ERR("Blocking transition since pending was %lx\n",
			  o->pending);
		return -EBUSY;
	}

	switch (state) {
	case BNX2X_Q_STATE_RESET:
		if (cmd == BNX2X_Q_CMD_INIT)
			next_state = BNX2X_Q_STATE_INITIALIZED;

		break;
	case BNX2X_Q_STATE_INITIALIZED:
		if (cmd == BNX2X_Q_CMD_SETUP) {
			if (test_bit(BNX2X_Q_FLG_ACTIVE,
				     &params->params.setup.flags))
				next_state = BNX2X_Q_STATE_ACTIVE;
			else
				next_state = BNX2X_Q_STATE_INACTIVE;
		}

		break;
	case BNX2X_Q_STATE_ACTIVE:
		if (cmd == BNX2X_Q_CMD_DEACTIVATE)
			next_state = BNX2X_Q_STATE_INACTIVE;

		else if ((cmd == BNX2X_Q_CMD_EMPTY) ||
			 (cmd == BNX2X_Q_CMD_UPDATE_TPA))
			next_state = BNX2X_Q_STATE_ACTIVE;

		else if (cmd == BNX2X_Q_CMD_SETUP_TX_ONLY) {
			next_state = BNX2X_Q_STATE_MULTI_COS;
			next_tx_only = 1;
		}

		else if (cmd == BNX2X_Q_CMD_HALT)
			next_state = BNX2X_Q_STATE_STOPPED;

		else if (cmd == BNX2X_Q_CMD_UPDATE) {
			/* If "active" state change is requested, update the
			 *  state accordingly.
			 */
			if (test_bit(BNX2X_Q_UPDATE_ACTIVATE_CHNG,
				     &update_params->update_flags) &&
			    !test_bit(BNX2X_Q_UPDATE_ACTIVATE,
				      &update_params->update_flags))
				next_state = BNX2X_Q_STATE_INACTIVE;
			else
				next_state = BNX2X_Q_STATE_ACTIVE;
		}

		break;
	case BNX2X_Q_STATE_MULTI_COS:
		if (cmd == BNX2X_Q_CMD_TERMINATE)
			next_state = BNX2X_Q_STATE_MCOS_TERMINATED;

		else if (cmd == BNX2X_Q_CMD_SETUP_TX_ONLY) {
			next_state = BNX2X_Q_STATE_MULTI_COS;
			next_tx_only = o->num_tx_only + 1;
		}

		else if ((cmd == BNX2X_Q_CMD_EMPTY) ||
			 (cmd == BNX2X_Q_CMD_UPDATE_TPA))
			next_state = BNX2X_Q_STATE_MULTI_COS;

		else if (cmd == BNX2X_Q_CMD_UPDATE) {
			/* If "active" state change is requested, update the
			 *  state accordingly.
			 */
			if (test_bit(BNX2X_Q_UPDATE_ACTIVATE_CHNG,
				     &update_params->update_flags) &&
			    !test_bit(BNX2X_Q_UPDATE_ACTIVATE,
				      &update_params->update_flags))
				next_state = BNX2X_Q_STATE_INACTIVE;
			else
				next_state = BNX2X_Q_STATE_MULTI_COS;
		}

		break;
	case BNX2X_Q_STATE_MCOS_TERMINATED:
		if (cmd == BNX2X_Q_CMD_CFC_DEL) {
			next_tx_only = o->num_tx_only - 1;
			if (next_tx_only == 0)
				next_state = BNX2X_Q_STATE_ACTIVE;
			else
				next_state = BNX2X_Q_STATE_MULTI_COS;
		}

		break;
	case BNX2X_Q_STATE_INACTIVE:
		if (cmd == BNX2X_Q_CMD_ACTIVATE)
			next_state = BNX2X_Q_STATE_ACTIVE;

		else if ((cmd == BNX2X_Q_CMD_EMPTY) ||
			 (cmd == BNX2X_Q_CMD_UPDATE_TPA))
			next_state = BNX2X_Q_STATE_INACTIVE;

		else if (cmd == BNX2X_Q_CMD_HALT)
			next_state = BNX2X_Q_STATE_STOPPED;

		else if (cmd == BNX2X_Q_CMD_UPDATE) {
			/* If "active" state change is requested, update the
			 * state accordingly.
			 */
			if (test_bit(BNX2X_Q_UPDATE_ACTIVATE_CHNG,
				     &update_params->update_flags) &&
			    test_bit(BNX2X_Q_UPDATE_ACTIVATE,
				     &update_params->update_flags)){
				if (o->num_tx_only == 0)
					next_state = BNX2X_Q_STATE_ACTIVE;
				else /* tx only queues exist for this queue */
					next_state = BNX2X_Q_STATE_MULTI_COS;
			} else
				next_state = BNX2X_Q_STATE_INACTIVE;
		}

		break;
	case BNX2X_Q_STATE_STOPPED:
		if (cmd == BNX2X_Q_CMD_TERMINATE)
			next_state = BNX2X_Q_STATE_TERMINATED;

		break;
	case BNX2X_Q_STATE_TERMINATED:
		if (cmd == BNX2X_Q_CMD_CFC_DEL)
			next_state = BNX2X_Q_STATE_RESET;

		break;
	default:
		BNX2X_ERR("Illegal state: %d\n", state);
	}

	/* Transition is assured */
	if (next_state != BNX2X_Q_STATE_MAX) {
		DP(BNX2X_MSG_SP, "Good state transition: %d(%d)->%d\n",
				 state, cmd, next_state);
		o->next_state = next_state;
		o->next_tx_only = next_tx_only;
		return 0;
	}

	DP(BNX2X_MSG_SP, "Bad state transition request: %d %d\n", state, cmd);

	return -EINVAL;
}