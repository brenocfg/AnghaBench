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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct be_mcc_wrb {int dummy; } ;
struct be_cmd_resp_loopback_test {int /*<<< orphan*/  status; } ;
struct TYPE_2__ {void* timeout; } ;
struct be_cmd_req_loopback_test {void* loopback_type; void* num_pkts; void* pkt_size; void* dest_port; void* src_port; int /*<<< orphan*/  pattern; TYPE_1__ hdr; } ;
struct be_adapter {int /*<<< orphan*/  mcc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_LOWLEVEL ; 
 int EBUSY ; 
 int /*<<< orphan*/  OPCODE_LOWLEVEL_LOOPBACK_TEST ; 
 int be_mcc_notify_wait (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,int /*<<< orphan*/ *) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 void* embedded_payload (struct be_mcc_wrb*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct be_adapter*) ; 

int be_cmd_loopback_test(struct be_adapter *adapter, u32 port_num,
		u32 loopback_type, u32 pkt_size, u32 num_pkts, u64 pattern)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_loopback_test *req;
	int status;

	spin_lock_bh(&adapter->mcc_lock);

	wrb = wrb_from_mccq(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}

	req = embedded_payload(wrb);

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_LOWLEVEL,
			OPCODE_LOWLEVEL_LOOPBACK_TEST, sizeof(*req), wrb, NULL);
	req->hdr.timeout = cpu_to_le32(4);

	req->pattern = cpu_to_le64(pattern);
	req->src_port = cpu_to_le32(port_num);
	req->dest_port = cpu_to_le32(port_num);
	req->pkt_size = cpu_to_le32(pkt_size);
	req->num_pkts = cpu_to_le32(num_pkts);
	req->loopback_type = cpu_to_le32(loopback_type);

	status = be_mcc_notify_wait(adapter);
	if (!status) {
		struct be_cmd_resp_loopback_test *resp = embedded_payload(wrb);
		status = le32_to_cpu(resp->status);
	}

err:
	spin_unlock_bh(&adapter->mcc_lock);
	return status;
}