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
typedef  scalar_t__ u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct be_mcc_wrb {int dummy; } ;
struct be_dma_mem {struct be_cmd_resp_ddrdma_test* va; int /*<<< orphan*/  size; } ;
struct be_cmd_resp_ddrdma_test {scalar_t__ snd_err; scalar_t__* snd_buff; int /*<<< orphan*/  rcv_buff; int /*<<< orphan*/  byte_count; int /*<<< orphan*/  pattern; int /*<<< orphan*/  hdr; } ;
struct be_cmd_req_ddrdma_test {scalar_t__ snd_err; scalar_t__* snd_buff; int /*<<< orphan*/  rcv_buff; int /*<<< orphan*/  byte_count; int /*<<< orphan*/  pattern; int /*<<< orphan*/  hdr; } ;
struct be_adapter {int /*<<< orphan*/  mcc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_LOWLEVEL ; 
 int EBUSY ; 
 int /*<<< orphan*/  OPCODE_LOWLEVEL_HOST_DDR_DMA ; 
 int be_mcc_notify_wait (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct be_mcc_wrb*,struct be_dma_mem*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct be_adapter*) ; 

int be_cmd_ddr_dma_test(struct be_adapter *adapter, u64 pattern,
				u32 byte_cnt, struct be_dma_mem *cmd)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_ddrdma_test *req;
	int status;
	int i, j = 0;

	spin_lock_bh(&adapter->mcc_lock);

	wrb = wrb_from_mccq(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}
	req = cmd->va;
	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_LOWLEVEL,
			OPCODE_LOWLEVEL_HOST_DDR_DMA, cmd->size, wrb, cmd);

	req->pattern = cpu_to_le64(pattern);
	req->byte_count = cpu_to_le32(byte_cnt);
	for (i = 0; i < byte_cnt; i++) {
		req->snd_buff[i] = (u8)(pattern >> (j*8));
		j++;
		if (j > 7)
			j = 0;
	}

	status = be_mcc_notify_wait(adapter);

	if (!status) {
		struct be_cmd_resp_ddrdma_test *resp;
		resp = cmd->va;
		if ((memcmp(resp->rcv_buff, req->snd_buff, byte_cnt) != 0) ||
				resp->snd_err) {
			status = -1;
		}
	}

err:
	spin_unlock_bh(&adapter->mcc_lock);
	return status;
}