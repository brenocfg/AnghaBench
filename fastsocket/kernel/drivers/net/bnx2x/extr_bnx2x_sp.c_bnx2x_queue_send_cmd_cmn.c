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
struct bnx2x_queue_state_params {int cmd; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
#define  BNX2X_Q_CMD_ACTIVATE 137 
#define  BNX2X_Q_CMD_CFC_DEL 136 
#define  BNX2X_Q_CMD_DEACTIVATE 135 
#define  BNX2X_Q_CMD_EMPTY 134 
#define  BNX2X_Q_CMD_HALT 133 
#define  BNX2X_Q_CMD_INIT 132 
#define  BNX2X_Q_CMD_SETUP_TX_ONLY 131 
#define  BNX2X_Q_CMD_TERMINATE 130 
#define  BNX2X_Q_CMD_UPDATE 129 
#define  BNX2X_Q_CMD_UPDATE_TPA 128 
 int EINVAL ; 
 int bnx2x_q_init (struct bnx2x*,struct bnx2x_queue_state_params*) ; 
 int bnx2x_q_send_activate (struct bnx2x*,struct bnx2x_queue_state_params*) ; 
 int bnx2x_q_send_cfc_del (struct bnx2x*,struct bnx2x_queue_state_params*) ; 
 int bnx2x_q_send_deactivate (struct bnx2x*,struct bnx2x_queue_state_params*) ; 
 int bnx2x_q_send_empty (struct bnx2x*,struct bnx2x_queue_state_params*) ; 
 int bnx2x_q_send_halt (struct bnx2x*,struct bnx2x_queue_state_params*) ; 
 int bnx2x_q_send_setup_tx_only (struct bnx2x*,struct bnx2x_queue_state_params*) ; 
 int bnx2x_q_send_terminate (struct bnx2x*,struct bnx2x_queue_state_params*) ; 
 int bnx2x_q_send_update (struct bnx2x*,struct bnx2x_queue_state_params*) ; 
 int bnx2x_q_send_update_tpa (struct bnx2x*,struct bnx2x_queue_state_params*) ; 

__attribute__((used)) static inline int bnx2x_queue_send_cmd_cmn(struct bnx2x *bp,
					struct bnx2x_queue_state_params *params)
{
	switch (params->cmd) {
	case BNX2X_Q_CMD_INIT:
		return bnx2x_q_init(bp, params);
	case BNX2X_Q_CMD_SETUP_TX_ONLY:
		return bnx2x_q_send_setup_tx_only(bp, params);
	case BNX2X_Q_CMD_DEACTIVATE:
		return bnx2x_q_send_deactivate(bp, params);
	case BNX2X_Q_CMD_ACTIVATE:
		return bnx2x_q_send_activate(bp, params);
	case BNX2X_Q_CMD_UPDATE:
		return bnx2x_q_send_update(bp, params);
	case BNX2X_Q_CMD_UPDATE_TPA:
		return bnx2x_q_send_update_tpa(bp, params);
	case BNX2X_Q_CMD_HALT:
		return bnx2x_q_send_halt(bp, params);
	case BNX2X_Q_CMD_CFC_DEL:
		return bnx2x_q_send_cfc_del(bp, params);
	case BNX2X_Q_CMD_TERMINATE:
		return bnx2x_q_send_terminate(bp, params);
	case BNX2X_Q_CMD_EMPTY:
		return bnx2x_q_send_empty(bp, params);
	default:
		BNX2X_ERR("Unknown command: %d\n", params->cmd);
		return -EINVAL;
	}
}