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
typedef  int u64 ;
struct intr_info {int member_0; char* member_1; int member_2; int member_3; int /*<<< orphan*/  const member_4; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; } ;

/* Variables and functions */
#define  EGRESS_SIZE_ERR 145 
#define  ERR_BAD_DB_PIDX0 144 
#define  ERR_BAD_DB_PIDX1 143 
#define  ERR_BAD_DB_PIDX2 142 
#define  ERR_BAD_DB_PIDX3 141 
#define  ERR_CPL_EXCEED_IQE_SIZE 140 
#define  ERR_CPL_OPCODE_0 139 
#define  ERR_DATA_CPL_ON_HIGH_QID0 138 
#define  ERR_DATA_CPL_ON_HIGH_QID1 137 
#define  ERR_EGR_CTXT_PRIO 136 
#define  ERR_ING_CTXT_PRIO 135 
#define  ERR_INVALID_CIDX_INC 134 
#define  F_DBFIFO_HP_INT 133 
#define  F_DBFIFO_LP_INT 132 
#define  F_ERR_DROPPED_DB 131 
#define  INGRESS_SIZE_ERR 130 
 int /*<<< orphan*/  SGE_INT_CAUSE1 ; 
 int /*<<< orphan*/  SGE_INT_CAUSE2 ; 
 int /*<<< orphan*/  SGE_INT_CAUSE3 ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ ,char*,unsigned long long) ; 
#define  t4_db_dropped 129 
#define  t4_db_full 128 
 int /*<<< orphan*/  t4_fatal_err (struct adapter*) ; 
 scalar_t__ t4_handle_intr_status (struct adapter*,int /*<<< orphan*/ ,struct intr_info const*) ; 
 scalar_t__ t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sge_intr_handler(struct adapter *adapter)
{
	u64 v;

	static const struct intr_info sge_intr_info[] = {
		{ ERR_CPL_EXCEED_IQE_SIZE,
		  "SGE received CPL exceeding IQE size", -1, 1 },
		{ ERR_INVALID_CIDX_INC,
		  "SGE GTS CIDX increment too large", -1, 0 },
		{ ERR_CPL_OPCODE_0, "SGE received 0-length CPL", -1, 0 },
		{ F_DBFIFO_LP_INT, NULL, -1, 0, t4_db_full },
		{ F_DBFIFO_HP_INT, NULL, -1, 0, t4_db_full },
		{ F_ERR_DROPPED_DB, NULL, -1, 0, t4_db_dropped },
		{ ERR_DATA_CPL_ON_HIGH_QID1 | ERR_DATA_CPL_ON_HIGH_QID0,
		  "SGE IQID > 1023 received CPL for FL", -1, 0 },
		{ ERR_BAD_DB_PIDX3, "SGE DBP 3 pidx increment too large", -1,
		  0 },
		{ ERR_BAD_DB_PIDX2, "SGE DBP 2 pidx increment too large", -1,
		  0 },
		{ ERR_BAD_DB_PIDX1, "SGE DBP 1 pidx increment too large", -1,
		  0 },
		{ ERR_BAD_DB_PIDX0, "SGE DBP 0 pidx increment too large", -1,
		  0 },
		{ ERR_ING_CTXT_PRIO,
		  "SGE too many priority ingress contexts", -1, 0 },
		{ ERR_EGR_CTXT_PRIO,
		  "SGE too many priority egress contexts", -1, 0 },
		{ INGRESS_SIZE_ERR, "SGE illegal ingress QID", -1, 0 },
		{ EGRESS_SIZE_ERR, "SGE illegal egress QID", -1, 0 },
		{ 0 }
	};

	v = (u64)t4_read_reg(adapter, SGE_INT_CAUSE1) |
		((u64)t4_read_reg(adapter, SGE_INT_CAUSE2) << 32);
	if (v) {
		dev_alert(adapter->pdev_dev, "SGE parity error (%#llx)\n",
				(unsigned long long)v);
		t4_write_reg(adapter, SGE_INT_CAUSE1, v);
		t4_write_reg(adapter, SGE_INT_CAUSE2, v >> 32);
	}

	if (t4_handle_intr_status(adapter, SGE_INT_CAUSE3, sge_intr_info) ||
	    v != 0)
		t4_fatal_err(adapter);
}