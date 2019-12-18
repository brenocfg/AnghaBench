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
typedef  int u64 ;
struct qlcnic_nic_req {void** words; void* req_hdr; void* qhdr; } ;
struct qlcnic_adapter {TYPE_1__* netdev; scalar_t__ portnum; } ;
struct cmd_desc_type0 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ QLCNIC_ENABLE_TYPE_C_RSS ; 
 int QLCNIC_H2C_OPCODE_CONFIG_RSS ; 
 int QLCNIC_HOST_REQUEST ; 
 scalar_t__ QLCNIC_RSS_FEATURE_FLAG ; 
 int QLCNIC_RSS_HASHTYPE_IP_TCP ; 
 scalar_t__ QLCNIC_RSS_IND_TABLE_MASK ; 
 void* cpu_to_le64 (int const) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (struct qlcnic_nic_req*,int /*<<< orphan*/ ,int) ; 
 int qlcnic_send_cmd_descs (struct qlcnic_adapter*,struct cmd_desc_type0*,int) ; 

int qlcnic_82xx_config_rss(struct qlcnic_adapter *adapter, int enable)
{
	struct qlcnic_nic_req req;
	u64 word;
	int i, rv;

	static const u64 key[] = {
		0xbeac01fa6a42b73bULL, 0x8030f20c77cb2da3ULL,
		0xae7b30b4d0ca2bcbULL, 0x43a38fb04167253dULL,
		0x255b0ec26d5a56daULL
	};

	memset(&req, 0, sizeof(struct qlcnic_nic_req));
	req.qhdr = cpu_to_le64(QLCNIC_HOST_REQUEST << 23);

	word = QLCNIC_H2C_OPCODE_CONFIG_RSS | ((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);

	/*
	 * RSS request:
	 * bits 3-0: hash_method
	 *      5-4: hash_type_ipv4
	 *	7-6: hash_type_ipv6
	 *	  8: enable
	 *        9: use indirection table
	 *       10: type-c rss
	 *	 11: udp rss
	 *    47-12: reserved
	 *    62-48: indirection table mask
	 *	 63: feature flag
	 */
	word =  ((u64)(QLCNIC_RSS_HASHTYPE_IP_TCP & 0x3) << 4) |
		((u64)(QLCNIC_RSS_HASHTYPE_IP_TCP & 0x3) << 6) |
		((u64)(enable & 0x1) << 8) |
		((u64)QLCNIC_RSS_IND_TABLE_MASK << 48) |
		(u64)QLCNIC_ENABLE_TYPE_C_RSS |
		(u64)QLCNIC_RSS_FEATURE_FLAG;

	req.words[0] = cpu_to_le64(word);
	for (i = 0; i < 5; i++)
		req.words[i+1] = cpu_to_le64(key[i]);

	rv = qlcnic_send_cmd_descs(adapter, (struct cmd_desc_type0 *)&req, 1);
	if (rv != 0)
		dev_err(&adapter->netdev->dev, "could not configure RSS\n");

	return rv;
}