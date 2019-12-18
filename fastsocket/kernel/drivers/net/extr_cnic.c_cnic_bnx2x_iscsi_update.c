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
typedef  int /*<<< orphan*/  u32 ;
struct kwqe {int dummy; } ;
struct iscsi_kwqe_conn_update {int /*<<< orphan*/  context_id; } ;
struct cnic_local {int dummy; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_SW_CID (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ISCSI_CONNECTION_TYPE ; 
 int /*<<< orphan*/  ISCSI_RAMROD_CMD_ID_UPDATE_CONN ; 
 void* cnic_get_kwqe_16_data (struct cnic_local*,int /*<<< orphan*/ ,union l5cm_specific_data*) ; 
 scalar_t__ cnic_get_l5_cid (struct cnic_local*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cnic_submit_kwqe_16 (struct cnic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union l5cm_specific_data*) ; 
 int /*<<< orphan*/  memcpy (void*,struct kwqe*,int) ; 

__attribute__((used)) static int cnic_bnx2x_iscsi_update(struct cnic_dev *dev, struct kwqe *kwqe)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct iscsi_kwqe_conn_update *req =
		(struct iscsi_kwqe_conn_update *) kwqe;
	void *data;
	union l5cm_specific_data l5_data;
	u32 l5_cid, cid = BNX2X_SW_CID(req->context_id);
	int ret;

	if (cnic_get_l5_cid(cp, cid, &l5_cid) != 0)
		return -EINVAL;

	data = cnic_get_kwqe_16_data(cp, l5_cid, &l5_data);
	if (!data)
		return -ENOMEM;

	memcpy(data, kwqe, sizeof(struct kwqe));

	ret = cnic_submit_kwqe_16(dev, ISCSI_RAMROD_CMD_ID_UPDATE_CONN,
			req->context_id, ISCSI_CONNECTION_TYPE, &l5_data);
	return ret;
}