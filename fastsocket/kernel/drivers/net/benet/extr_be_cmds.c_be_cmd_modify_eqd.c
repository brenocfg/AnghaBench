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
typedef  int u32 ;
struct be_mcc_wrb {int dummy; } ;
struct be_cmd_req_modify_eq_delay {TYPE_1__* delay; void* num_eq; int /*<<< orphan*/  hdr; } ;
struct be_adapter {int /*<<< orphan*/  mcc_lock; } ;
struct TYPE_2__ {void* delay_multiplier; scalar_t__ phase; void* eq_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int EBUSY ; 
 int /*<<< orphan*/  OPCODE_COMMON_MODIFY_EQ_DELAY ; 
 int /*<<< orphan*/  be_mcc_notify (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,int /*<<< orphan*/ *) ; 
 void* cpu_to_le32 (int) ; 
 struct be_cmd_req_modify_eq_delay* embedded_payload (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct be_adapter*) ; 

int be_cmd_modify_eqd(struct be_adapter *adapter, u32 eq_id, u32 eqd)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_modify_eq_delay *req;
	int status = 0;

	spin_lock_bh(&adapter->mcc_lock);

	wrb = wrb_from_mccq(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}
	req = embedded_payload(wrb);

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
		OPCODE_COMMON_MODIFY_EQ_DELAY, sizeof(*req), wrb, NULL);

	req->num_eq = cpu_to_le32(1);
	req->delay[0].eq_id = cpu_to_le32(eq_id);
	req->delay[0].phase = 0;
	req->delay[0].delay_multiplier = cpu_to_le32(eqd);

	be_mcc_notify(adapter);

err:
	spin_unlock_bh(&adapter->mcc_lock);
	return status;
}