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
typedef  int u64 ;
typedef  size_t u32 ;
struct status_desc {int /*<<< orphan*/ * status_desc_data; } ;
struct qlcnic_host_sds_ring {size_t consumer; int /*<<< orphan*/  crb_sts_consumer; int /*<<< orphan*/  num_desc; struct status_desc* desc_head; struct qlcnic_adapter* adapter; } ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
#define  QLCNIC_RESPONSE_DESC 128 
 int STATUS_OWNER_HOST ; 
 int /*<<< orphan*/  STATUS_OWNER_PHANTOM ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 size_t get_next_index (size_t,int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int qlcnic_get_sts_desc_cnt (int) ; 
 int qlcnic_get_sts_opcode (int) ; 
 int qlcnic_get_sts_type (int) ; 
 int /*<<< orphan*/  qlcnic_handle_fw_message (int,size_t,struct qlcnic_host_sds_ring*) ; 
 int /*<<< orphan*/  qlcnic_process_rcv_diag (struct qlcnic_adapter*,int,int) ; 
 int /*<<< orphan*/  writel (size_t,int /*<<< orphan*/ ) ; 

void qlcnic_82xx_process_rcv_ring_diag(struct qlcnic_host_sds_ring *sds_ring)
{
	struct qlcnic_adapter *adapter = sds_ring->adapter;
	struct status_desc *desc;
	u64 sts_data0;
	int ring, opcode, desc_cnt;

	u32 consumer = sds_ring->consumer;

	desc = &sds_ring->desc_head[consumer];
	sts_data0 = le64_to_cpu(desc->status_desc_data[0]);

	if (!(sts_data0 & STATUS_OWNER_HOST))
		return;

	desc_cnt = qlcnic_get_sts_desc_cnt(sts_data0);
	opcode = qlcnic_get_sts_opcode(sts_data0);
	switch (opcode) {
	case QLCNIC_RESPONSE_DESC:
		qlcnic_handle_fw_message(desc_cnt, consumer, sds_ring);
		break;
	default:
		ring = qlcnic_get_sts_type(sts_data0);
		qlcnic_process_rcv_diag(adapter, ring, sts_data0);
		break;
	}

	for (; desc_cnt > 0; desc_cnt--) {
		desc = &sds_ring->desc_head[consumer];
		desc->status_desc_data[0] = cpu_to_le64(STATUS_OWNER_PHANTOM);
		consumer = get_next_index(consumer, sds_ring->num_desc);
	}

	sds_ring->consumer = consumer;
	writel(consumer, sds_ring->crb_sts_consumer);
}