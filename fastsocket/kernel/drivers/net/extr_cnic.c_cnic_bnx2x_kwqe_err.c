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
typedef  scalar_t__ u32 ;
struct l4_kcq {scalar_t__ conn_id; scalar_t__ cid; int /*<<< orphan*/  status; } ;
struct kwqe {scalar_t__ kwqe_op_flag; scalar_t__ kwqe_info0; scalar_t__ kwqe_info1; } ;
struct kcqe {scalar_t__ kcqe_op_flag; scalar_t__ kcqe_info0; scalar_t__ kcqe_info2; int /*<<< orphan*/  kcqe_info1; } ;
struct fcoe_kwqe_conn_enable_disable {scalar_t__ context_id; scalar_t__ conn_id; } ;
struct cnic_local {int dummy; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;
typedef  int /*<<< orphan*/  kcqe ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_SW_CID (scalar_t__) ; 
 int CNIC_ULP_FCOE ; 
 int CNIC_ULP_ISCSI ; 
 int CNIC_ULP_L4 ; 
 int /*<<< orphan*/  FCOE_KCQE_COMPLETION_STATUS_PARITY_ERROR ; 
 scalar_t__ FCOE_KCQE_OPCODE_DESTROY_FUNC ; 
 scalar_t__ FCOE_KCQE_OPCODE_DISABLE_CONN ; 
 scalar_t__ FCOE_KWQE_OPCODE_DESTROY ; 
 scalar_t__ FCOE_KWQE_OPCODE_DISABLE_CONN ; 
 int /*<<< orphan*/  ISCSI_KCQE_COMPLETION_STATUS_PARITY_ERR ; 
 scalar_t__ ISCSI_KWQE_OPCODE_UPDATE_CONN ; 
 scalar_t__ KCQE_FLAGS_LAYER_MASK_L4 ; 
 scalar_t__ KCQE_FLAGS_LAYER_MASK_L5_FCOE ; 
 scalar_t__ KCQE_FLAGS_LAYER_MASK_L5_ISCSI ; 
 scalar_t__ KCQE_FLAGS_OPCODE_SHIFT ; 
 scalar_t__ KWQE_FLAGS_LAYER_MASK_L4 ; 
 scalar_t__ KWQE_FLAGS_LAYER_MASK_L5_FCOE ; 
 scalar_t__ KWQE_FLAGS_LAYER_MASK_L5_ISCSI ; 
 scalar_t__ KWQE_LAYER_MASK ; 
 scalar_t__ KWQE_OPCODE (scalar_t__) ; 
 int /*<<< orphan*/  L4_KCQE_COMPLETION_STATUS_PARITY_ERROR ; 
 scalar_t__ L4_KCQE_OPCODE_VALUE_CLOSE_COMP ; 
 scalar_t__ L4_KCQE_OPCODE_VALUE_CONNECT_COMPLETE ; 
 scalar_t__ L4_KCQE_OPCODE_VALUE_RESET_COMP ; 
 scalar_t__ L4_KWQE_OPCODE_VALUE_CLOSE ; 
 scalar_t__ L4_KWQE_OPCODE_VALUE_CONNECT1 ; 
 scalar_t__ L4_KWQE_OPCODE_VALUE_RESET ; 
 int /*<<< orphan*/  cnic_get_l5_cid (struct cnic_local*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  cnic_reply_bnx2x_kcqes (struct cnic_dev*,int,struct kcqe**,int) ; 
 int /*<<< orphan*/  memset (struct kcqe*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cnic_bnx2x_kwqe_err(struct cnic_dev *dev, struct kwqe *kwqe)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct kcqe kcqe;
	struct kcqe *cqes[1];
	u32 cid;
	u32 opcode = KWQE_OPCODE(kwqe->kwqe_op_flag);
	u32 layer_code = kwqe->kwqe_op_flag & KWQE_LAYER_MASK;
	u32 kcqe_op;
	int ulp_type;

	cid = kwqe->kwqe_info0;
	memset(&kcqe, 0, sizeof(kcqe));

	if (layer_code == KWQE_FLAGS_LAYER_MASK_L5_FCOE) {
		u32 l5_cid = 0;

		ulp_type = CNIC_ULP_FCOE;
		if (opcode == FCOE_KWQE_OPCODE_DISABLE_CONN) {
			struct fcoe_kwqe_conn_enable_disable *req;

			req = (struct fcoe_kwqe_conn_enable_disable *) kwqe;
			kcqe_op = FCOE_KCQE_OPCODE_DISABLE_CONN;
			cid = req->context_id;
			l5_cid = req->conn_id;
		} else if (opcode == FCOE_KWQE_OPCODE_DESTROY) {
			kcqe_op = FCOE_KCQE_OPCODE_DESTROY_FUNC;
		} else {
			return;
		}
		kcqe.kcqe_op_flag = kcqe_op << KCQE_FLAGS_OPCODE_SHIFT;
		kcqe.kcqe_op_flag |= KCQE_FLAGS_LAYER_MASK_L5_FCOE;
		kcqe.kcqe_info1 = FCOE_KCQE_COMPLETION_STATUS_PARITY_ERROR;
		kcqe.kcqe_info2 = cid;
		kcqe.kcqe_info0 = l5_cid;

	} else if (layer_code == KWQE_FLAGS_LAYER_MASK_L5_ISCSI) {
		ulp_type = CNIC_ULP_ISCSI;
		if (opcode == ISCSI_KWQE_OPCODE_UPDATE_CONN)
			cid = kwqe->kwqe_info1;

		kcqe.kcqe_op_flag = (opcode + 0x10) << KCQE_FLAGS_OPCODE_SHIFT;
		kcqe.kcqe_op_flag |= KCQE_FLAGS_LAYER_MASK_L5_ISCSI;
		kcqe.kcqe_info1 = ISCSI_KCQE_COMPLETION_STATUS_PARITY_ERR;
		kcqe.kcqe_info2 = cid;
		cnic_get_l5_cid(cp, BNX2X_SW_CID(cid), &kcqe.kcqe_info0);

	} else if (layer_code == KWQE_FLAGS_LAYER_MASK_L4) {
		struct l4_kcq *l4kcqe = (struct l4_kcq *) &kcqe;

		ulp_type = CNIC_ULP_L4;
		if (opcode == L4_KWQE_OPCODE_VALUE_CONNECT1)
			kcqe_op = L4_KCQE_OPCODE_VALUE_CONNECT_COMPLETE;
		else if (opcode == L4_KWQE_OPCODE_VALUE_RESET)
			kcqe_op = L4_KCQE_OPCODE_VALUE_RESET_COMP;
		else if (opcode == L4_KWQE_OPCODE_VALUE_CLOSE)
			kcqe_op = L4_KCQE_OPCODE_VALUE_CLOSE_COMP;
		else
			return;

		kcqe.kcqe_op_flag = (kcqe_op << KCQE_FLAGS_OPCODE_SHIFT) |
				    KCQE_FLAGS_LAYER_MASK_L4;
		l4kcqe->status = L4_KCQE_COMPLETION_STATUS_PARITY_ERROR;
		l4kcqe->cid = cid;
		cnic_get_l5_cid(cp, BNX2X_SW_CID(cid), &l4kcqe->conn_id);
	} else {
		return;
	}

	cqes[0] = &kcqe;
	cnic_reply_bnx2x_kcqes(dev, ulp_type, cqes, 1);
}