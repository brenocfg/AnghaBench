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
struct TYPE_4__ {int /*<<< orphan*/  cmdq_ci; } ;
struct bfi_msgq_i2h_db {TYPE_2__ idx; } ;
struct bfi_mbmsg {int dummy; } ;
struct bfa_msgq_cmdq {int /*<<< orphan*/  pending_q; scalar_t__ consumer_index; } ;
struct bfa_msgq_cmd_entry {int /*<<< orphan*/  qe; TYPE_1__* msg_hdr; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_entries; } ;

/* Variables and functions */
 scalar_t__ BFA_MSGQ_FREE_CNT (struct bfa_msgq_cmdq*) ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  CMDQ_E_POST ; 
 int /*<<< orphan*/  __cmd_copy (struct bfa_msgq_cmdq*,struct bfa_msgq_cmd_entry*) ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bfa_msgq_cmdq*,int /*<<< orphan*/ ) ; 
 scalar_t__ bfa_q_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_cmdq_ent_cbfn (struct bfa_msgq_cmd_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_msgq_cmdq_ci_update(struct bfa_msgq_cmdq *cmdq, struct bfi_mbmsg *mb)
{
	struct bfi_msgq_i2h_db *dbell = (struct bfi_msgq_i2h_db *)mb;
	struct bfa_msgq_cmd_entry *cmd;
	int posted = 0;

	cmdq->consumer_index = ntohs(dbell->idx.cmdq_ci);

	/* Walk through pending list to see if the command can be posted */
	while (!list_empty(&cmdq->pending_q)) {
		cmd =
		(struct bfa_msgq_cmd_entry *)bfa_q_first(&cmdq->pending_q);
		if (ntohs(cmd->msg_hdr->num_entries) <=
			BFA_MSGQ_FREE_CNT(cmdq)) {
			list_del(&cmd->qe);
			__cmd_copy(cmdq, cmd);
			posted = 1;
			call_cmdq_ent_cbfn(cmd, BFA_STATUS_OK);
		} else {
			break;
		}
	}

	if (posted)
		bfa_fsm_send_event(cmdq, CMDQ_E_POST);
}