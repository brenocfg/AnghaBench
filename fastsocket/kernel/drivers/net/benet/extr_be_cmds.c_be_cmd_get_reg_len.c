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
struct be_mcc_wrb {int dummy; } ;
struct be_cmd_resp_get_fat {scalar_t__ log_size; } ;
struct be_cmd_req_get_fat {int /*<<< orphan*/  fat_operation; int /*<<< orphan*/  hdr; } ;
struct be_adapter {int /*<<< orphan*/  mcc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int EBUSY ; 
 int /*<<< orphan*/  OPCODE_COMMON_MANAGE_FAT ; 
 int /*<<< orphan*/  QUERY_FAT ; 
 int be_mcc_notify_wait (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* embedded_payload (struct be_mcc_wrb*) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct be_adapter*) ; 

int be_cmd_get_reg_len(struct be_adapter *adapter, u32 *log_size)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_get_fat *req;
	int status;

	spin_lock_bh(&adapter->mcc_lock);

	wrb = wrb_from_mccq(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}
	req = embedded_payload(wrb);

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
		OPCODE_COMMON_MANAGE_FAT, sizeof(*req), wrb, NULL);
	req->fat_operation = cpu_to_le32(QUERY_FAT);
	status = be_mcc_notify_wait(adapter);
	if (!status) {
		struct be_cmd_resp_get_fat *resp = embedded_payload(wrb);
		if (log_size && resp->log_size)
			*log_size = le32_to_cpu(resp->log_size) -
					sizeof(u32);
	}
err:
	spin_unlock_bh(&adapter->mcc_lock);
	return status;
}