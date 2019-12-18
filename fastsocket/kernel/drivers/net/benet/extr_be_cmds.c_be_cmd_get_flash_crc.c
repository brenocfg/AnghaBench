#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct be_mcc_wrb {int dummy; } ;
struct TYPE_2__ {void* data_buf_size; void* offset; void* op_code; void* op_type; } ;
struct be_cmd_read_flash_crc {int /*<<< orphan*/  crc; TYPE_1__ params; int /*<<< orphan*/  hdr; } ;
struct be_adapter {int /*<<< orphan*/  mcc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int EBUSY ; 
 int FLASHROM_OPER_REPORT ; 
 int /*<<< orphan*/  OPCODE_COMMON_READ_FLASHROM ; 
 int OPTYPE_REDBOOT ; 
 int be_mcc_notify_wait (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,int /*<<< orphan*/ *) ; 
 void* cpu_to_le32 (int) ; 
 struct be_cmd_read_flash_crc* embedded_payload (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct be_adapter*) ; 

int be_cmd_get_flash_crc(struct be_adapter *adapter, u8 *flashed_crc,
			 int offset)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_read_flash_crc *req;
	int status;

	spin_lock_bh(&adapter->mcc_lock);

	wrb = wrb_from_mccq(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}
	req = embedded_payload(wrb);

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			       OPCODE_COMMON_READ_FLASHROM, sizeof(*req),
			       wrb, NULL);

	req->params.op_type = cpu_to_le32(OPTYPE_REDBOOT);
	req->params.op_code = cpu_to_le32(FLASHROM_OPER_REPORT);
	req->params.offset = cpu_to_le32(offset);
	req->params.data_buf_size = cpu_to_le32(0x4);

	status = be_mcc_notify_wait(adapter);
	if (!status)
		memcpy(flashed_crc, req->crc, 4);

err:
	spin_unlock_bh(&adapter->mcc_lock);
	return status;
}