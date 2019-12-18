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
typedef  int /*<<< orphan*/  u32 ;
struct kwqe {int dummy; } ;
struct kcqe {int dummy; } ;
struct iscsi_kwqe_init2 {int /*<<< orphan*/  max_cq_sqn; int /*<<< orphan*/ * error_bit_map; } ;
struct iscsi_kcqe {int /*<<< orphan*/  op_code; int /*<<< orphan*/  completion_status; } ;
struct cnic_local {int /*<<< orphan*/  pfid; } ;
struct cnic_dev {int /*<<< orphan*/  max_iscsi_conn; int /*<<< orphan*/  netdev; struct cnic_local* cnic_priv; } ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  kcqe ;

/* Variables and functions */
 scalar_t__ BAR_CSTRORM_INTMEM ; 
 scalar_t__ BAR_TSTRORM_INTMEM ; 
 scalar_t__ BAR_USTRORM_INTMEM ; 
 int /*<<< orphan*/  CNIC_ULP_ISCSI ; 
 int /*<<< orphan*/  CNIC_WR (struct cnic_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CNIC_WR16 (struct cnic_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ CSTORM_ISCSI_CQ_SQN_SIZE_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISCSI_KCQE_COMPLETION_STATUS_ISCSI_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ISCSI_KCQE_COMPLETION_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ISCSI_KCQE_OPCODE_INIT ; 
 scalar_t__ TSTORM_ISCSI_ERROR_BITMAP_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ USTORM_ISCSI_CQ_SQN_SIZE_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ USTORM_ISCSI_ERROR_BITMAP_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnic_reply_bnx2x_kcqes (struct cnic_dev*,int /*<<< orphan*/ ,struct kcqe**,int) ; 
 int /*<<< orphan*/  memset (struct iscsi_kcqe*,int /*<<< orphan*/ ,int) ; 
 struct bnx2x* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cnic_bnx2x_iscsi_init2(struct cnic_dev *dev, struct kwqe *kwqe)
{
	struct iscsi_kwqe_init2 *req2 = (struct iscsi_kwqe_init2 *) kwqe;
	struct cnic_local *cp = dev->cnic_priv;
	struct bnx2x *bp = netdev_priv(dev->netdev);
	u32 pfid = cp->pfid;
	struct iscsi_kcqe kcqe;
	struct kcqe *cqes[1];

	memset(&kcqe, 0, sizeof(kcqe));
	if (!dev->max_iscsi_conn) {
		kcqe.completion_status =
			ISCSI_KCQE_COMPLETION_STATUS_ISCSI_NOT_SUPPORTED;
		goto done;
	}

	CNIC_WR(dev, BAR_TSTRORM_INTMEM +
		TSTORM_ISCSI_ERROR_BITMAP_OFFSET(pfid), req2->error_bit_map[0]);
	CNIC_WR(dev, BAR_TSTRORM_INTMEM +
		TSTORM_ISCSI_ERROR_BITMAP_OFFSET(pfid) + 4,
		req2->error_bit_map[1]);

	CNIC_WR16(dev, BAR_USTRORM_INTMEM +
		  USTORM_ISCSI_CQ_SQN_SIZE_OFFSET(pfid), req2->max_cq_sqn);
	CNIC_WR(dev, BAR_USTRORM_INTMEM +
		USTORM_ISCSI_ERROR_BITMAP_OFFSET(pfid), req2->error_bit_map[0]);
	CNIC_WR(dev, BAR_USTRORM_INTMEM +
		USTORM_ISCSI_ERROR_BITMAP_OFFSET(pfid) + 4,
		req2->error_bit_map[1]);

	CNIC_WR16(dev, BAR_CSTRORM_INTMEM +
		  CSTORM_ISCSI_CQ_SQN_SIZE_OFFSET(pfid), req2->max_cq_sqn);

	kcqe.completion_status = ISCSI_KCQE_COMPLETION_STATUS_SUCCESS;

done:
	kcqe.op_code = ISCSI_KCQE_OPCODE_INIT;
	cqes[0] = (struct kcqe *) &kcqe;
	cnic_reply_bnx2x_kcqes(dev, CNIC_ULP_ISCSI, cqes, 1);

	return 0;
}