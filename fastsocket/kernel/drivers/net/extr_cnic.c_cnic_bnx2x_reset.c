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
typedef  union l5cm_specific_data {int dummy; } l5cm_specific_data ;
struct l4_kwq_reset_req {int /*<<< orphan*/  cid; } ;
struct kwqe {int dummy; } ;
struct cnic_dev {int dummy; } ;
typedef  int /*<<< orphan*/  l5_data ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_CONNECTION_TYPE ; 
 int /*<<< orphan*/  L5CM_RAMROD_CMD_ID_ABORT ; 
 int cnic_submit_kwqe_16 (struct cnic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union l5cm_specific_data*) ; 
 int /*<<< orphan*/  memset (union l5cm_specific_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cnic_bnx2x_reset(struct cnic_dev *dev, struct kwqe *kwqe)
{
	struct l4_kwq_reset_req *req = (struct l4_kwq_reset_req *) kwqe;
	union l5cm_specific_data l5_data;
	int ret;

	memset(&l5_data, 0, sizeof(l5_data));
	ret = cnic_submit_kwqe_16(dev, L5CM_RAMROD_CMD_ID_ABORT,
			req->cid, ISCSI_CONNECTION_TYPE, &l5_data);
	return ret;
}