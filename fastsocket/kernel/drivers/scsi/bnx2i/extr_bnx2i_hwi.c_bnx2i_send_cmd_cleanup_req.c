#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bnx2i_hba {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  itt; } ;
struct bnx2i_cmd {TYPE_4__* conn; TYPE_3__ req; } ;
struct bnx2i_cleanup_request {scalar_t__ cq_index; int /*<<< orphan*/  itt; int /*<<< orphan*/  op_code; } ;
struct TYPE_8__ {TYPE_2__* ep; } ;
struct TYPE_5__ {scalar_t__ sq_prod_qe; } ;
struct TYPE_6__ {TYPE_1__ qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_OPCODE_CLEANUP_REQUEST ; 
 int /*<<< orphan*/  bnx2i_ring_dbell_update_sq_params (TYPE_4__*,int) ; 
 int /*<<< orphan*/  memset (struct bnx2i_cleanup_request*,int,int) ; 

void bnx2i_send_cmd_cleanup_req(struct bnx2i_hba *hba, struct bnx2i_cmd *cmd)
{
	struct bnx2i_cleanup_request *cmd_cleanup;

	cmd_cleanup =
		(struct bnx2i_cleanup_request *)cmd->conn->ep->qp.sq_prod_qe;
	memset(cmd_cleanup, 0x00, sizeof(struct bnx2i_cleanup_request));

	cmd_cleanup->op_code = ISCSI_OPCODE_CLEANUP_REQUEST;
	cmd_cleanup->itt = cmd->req.itt;
	cmd_cleanup->cq_index = 0; /* CQ# used for completion, 5771x only */

	bnx2i_ring_dbell_update_sq_params(cmd->conn, 1);
}