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
struct l4_kwq_update_pg {int /*<<< orphan*/  pg_cid; int /*<<< orphan*/  pg_host_opaque; } ;
struct l4_kcq {int /*<<< orphan*/  op_code; int /*<<< orphan*/  pg_cid; int /*<<< orphan*/  pg_host_opaque; } ;
struct kwqe {int dummy; } ;
struct kcqe {int dummy; } ;
struct cnic_dev {int dummy; } ;
typedef  int /*<<< orphan*/  kcqe ;

/* Variables and functions */
 int /*<<< orphan*/  CNIC_ULP_L4 ; 
 int /*<<< orphan*/  L4_KCQE_OPCODE_VALUE_UPDATE_PG ; 
 int /*<<< orphan*/  cnic_reply_bnx2x_kcqes (struct cnic_dev*,int /*<<< orphan*/ ,struct kcqe**,int) ; 
 int /*<<< orphan*/  memset (struct l4_kcq*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cnic_bnx2x_update_pg(struct cnic_dev *dev, struct kwqe *kwqe)
{
	struct l4_kwq_update_pg *req = (struct l4_kwq_update_pg *) kwqe;
	struct l4_kcq kcqe;
	struct kcqe *cqes[1];

	memset(&kcqe, 0, sizeof(kcqe));
	kcqe.pg_host_opaque = req->pg_host_opaque;
	kcqe.pg_cid = req->pg_cid;
	kcqe.op_code = L4_KCQE_OPCODE_VALUE_UPDATE_PG;
	cqes[0] = (struct kcqe *) &kcqe;
	cnic_reply_bnx2x_kcqes(dev, CNIC_ULP_L4, cqes, 1);
	return 0;
}