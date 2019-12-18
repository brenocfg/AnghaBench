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
struct be_mcc_wrb {int dummy; } ;
struct be_cmd_resp_set_func_cap {int /*<<< orphan*/  cap_flags; } ;
struct be_cmd_req_set_func_cap {void* cap_flags; void* valid_cap_flags; int /*<<< orphan*/  hdr; } ;
struct be_adapter {int be3_native; int /*<<< orphan*/  mbox_lock; } ;

/* Variables and functions */
 int CAPABILITY_BE3_NATIVE_ERX_API ; 
 int CAPABILITY_SW_TIMESTAMPS ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int EBUSY ; 
 int /*<<< orphan*/  OPCODE_COMMON_SET_DRIVER_FUNCTION_CAP ; 
 int be_mbox_notify_wait (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,int /*<<< orphan*/ *) ; 
 void* cpu_to_le32 (int) ; 
 void* embedded_payload (struct be_mcc_wrb*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mbox (struct be_adapter*) ; 

int be_cmd_req_native_mode(struct be_adapter *adapter)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_set_func_cap *req;
	int status;

	if (mutex_lock_interruptible(&adapter->mbox_lock))
		return -1;

	wrb = wrb_from_mbox(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}

	req = embedded_payload(wrb);

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
		OPCODE_COMMON_SET_DRIVER_FUNCTION_CAP, sizeof(*req), wrb, NULL);

	req->valid_cap_flags = cpu_to_le32(CAPABILITY_SW_TIMESTAMPS |
				CAPABILITY_BE3_NATIVE_ERX_API);
	req->cap_flags = cpu_to_le32(CAPABILITY_BE3_NATIVE_ERX_API);

	status = be_mbox_notify_wait(adapter);
	if (!status) {
		struct be_cmd_resp_set_func_cap *resp = embedded_payload(wrb);
		adapter->be3_native = le32_to_cpu(resp->cap_flags) &
					CAPABILITY_BE3_NATIVE_ERX_API;
	}
err:
	mutex_unlock(&adapter->mbox_lock);
	return status;
}