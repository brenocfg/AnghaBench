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
typedef  int u32 ;
struct qlcnic_nic_req {void** words; void* req_hdr; void* qhdr; } ;
struct qlcnic_adapter {scalar_t__ portnum; } ;
struct cmd_desc_type0 {int dummy; } ;

/* Variables and functions */
 int QLCNIC_H2C_OPCODE_SET_MAC_RECEIVE_MODE ; 
 int QLCNIC_HOST_REQUEST ; 
 void* cpu_to_le64 (int) ; 
 int /*<<< orphan*/  memset (struct qlcnic_nic_req*,int /*<<< orphan*/ ,int) ; 
 int qlcnic_send_cmd_descs (struct qlcnic_adapter*,struct cmd_desc_type0*,int) ; 

int qlcnic_82xx_nic_set_promisc(struct qlcnic_adapter *adapter, u32 mode)
{
	struct qlcnic_nic_req req;
	u64 word;

	memset(&req, 0, sizeof(struct qlcnic_nic_req));

	req.qhdr = cpu_to_le64(QLCNIC_HOST_REQUEST << 23);

	word = QLCNIC_H2C_OPCODE_SET_MAC_RECEIVE_MODE |
			((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);

	req.words[0] = cpu_to_le64(mode);

	return qlcnic_send_cmd_descs(adapter,
				(struct cmd_desc_type0 *)&req, 1);
}