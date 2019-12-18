#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct qlcnic_mailbox_metadata {scalar_t__ cmd; int in_args; int out_args; } ;
struct TYPE_6__ {int num; scalar_t__* arg; } ;
struct TYPE_4__ {int num; scalar_t__* arg; } ;
struct qlcnic_cmd_args {TYPE_3__ req; TYPE_1__ rsp; int /*<<< orphan*/  op_type; } ;
struct qlcnic_adapter {TYPE_2__* ahw; } ;
struct TYPE_5__ {int fw_hal_version; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct qlcnic_mailbox_metadata*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  QLC_83XX_FW_MBX_CMD ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 struct qlcnic_mailbox_metadata* qlcnic_83xx_mbx_tbl ; 

int qlcnic_83xx_alloc_mbx_args(struct qlcnic_cmd_args *mbx,
			       struct qlcnic_adapter *adapter, u32 type)
{
	int i, size;
	u32 temp;
	const struct qlcnic_mailbox_metadata *mbx_tbl;

	mbx_tbl = qlcnic_83xx_mbx_tbl;
	size = ARRAY_SIZE(qlcnic_83xx_mbx_tbl);
	for (i = 0; i < size; i++) {
		if (type == mbx_tbl[i].cmd) {
			mbx->op_type = QLC_83XX_FW_MBX_CMD;
			mbx->req.num = mbx_tbl[i].in_args;
			mbx->rsp.num = mbx_tbl[i].out_args;
			mbx->req.arg = kcalloc(mbx->req.num, sizeof(u32),
					       GFP_ATOMIC);
			if (!mbx->req.arg)
				return -ENOMEM;
			mbx->rsp.arg = kcalloc(mbx->rsp.num, sizeof(u32),
					       GFP_ATOMIC);
			if (!mbx->rsp.arg) {
				kfree(mbx->req.arg);
				mbx->req.arg = NULL;
				return -ENOMEM;
			}
			memset(mbx->req.arg, 0, sizeof(u32) * mbx->req.num);
			memset(mbx->rsp.arg, 0, sizeof(u32) * mbx->rsp.num);
			temp = adapter->ahw->fw_hal_version << 29;
			mbx->req.arg[0] = (type | (mbx->req.num << 16) | temp);
			return 0;
		}
	}
	return -EINVAL;
}