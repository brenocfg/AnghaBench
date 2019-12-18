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
struct kwqe {int dummy; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  op_code; } ;
struct fcoe_kwqe_conn_destroy {int /*<<< orphan*/  conn_id; int /*<<< orphan*/  context_id; TYPE_1__ hdr; } ;
struct bnx2fc_rport {int /*<<< orphan*/  fcoe_conn_id; int /*<<< orphan*/  context_id; } ;
struct bnx2fc_hba {TYPE_2__* cnic; } ;
struct TYPE_4__ {int (* submit_kwqes ) (TYPE_2__*,struct kwqe**,int) ;} ;

/* Variables and functions */
 int FCOE_KWQE_HEADER_LAYER_CODE_SHIFT ; 
 int FCOE_KWQE_LAYER_CODE ; 
 int /*<<< orphan*/  FCOE_KWQE_OPCODE_DESTROY_CONN ; 
 int /*<<< orphan*/  memset (struct fcoe_kwqe_conn_destroy*,int,int) ; 
 int stub1 (TYPE_2__*,struct kwqe**,int) ; 

int bnx2fc_send_session_destroy_req(struct bnx2fc_hba *hba,
					struct bnx2fc_rport *tgt)
{
	struct fcoe_kwqe_conn_destroy destroy_req;
	struct kwqe *kwqe_arr[2];
	int num_kwqes = 1;
	int rc = 0;

	memset(&destroy_req, 0x00, sizeof(struct fcoe_kwqe_conn_destroy));
	destroy_req.hdr.op_code = FCOE_KWQE_OPCODE_DESTROY_CONN;
	destroy_req.hdr.flags =
		(FCOE_KWQE_LAYER_CODE << FCOE_KWQE_HEADER_LAYER_CODE_SHIFT);

	destroy_req.context_id = tgt->context_id;
	destroy_req.conn_id = tgt->fcoe_conn_id;

	kwqe_arr[0] = (struct kwqe *) &destroy_req;

	if (hba->cnic && hba->cnic->submit_kwqes)
		rc = hba->cnic->submit_kwqes(hba->cnic, kwqe_arr, num_kwqes);

	return rc;
}