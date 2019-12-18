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
typedef  int /*<<< orphan*/  uint8_t ;
struct iscsi_iface_param_info {int /*<<< orphan*/  len; int /*<<< orphan*/  value; } ;
struct beiscsi_hba {int dummy; } ;
struct TYPE_2__ {scalar_t__* addr; } ;
struct be_cmd_get_def_gateway_resp {TYPE_1__ ip_addr; } ;
typedef  int /*<<< orphan*/  gtway_addr_set ;

/* Variables and functions */
 int /*<<< orphan*/  BE2_IPV4 ; 
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 int /*<<< orphan*/  IP_ACTION_ADD ; 
 int /*<<< orphan*/  IP_ACTION_DEL ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct be_cmd_get_def_gateway_resp*,int /*<<< orphan*/ ,int) ; 
 int mgmt_get_gateway (struct beiscsi_hba*,int /*<<< orphan*/ ,struct be_cmd_get_def_gateway_resp*) ; 
 int mgmt_modify_gateway (struct beiscsi_hba*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mgmt_set_gateway(struct beiscsi_hba *phba,
		     struct iscsi_iface_param_info *gateway_param)
{
	struct be_cmd_get_def_gateway_resp gtway_addr_set;
	uint8_t *gtway_addr;
	int rt_val;

	memset(&gtway_addr_set, 0, sizeof(gtway_addr_set));
	rt_val = mgmt_get_gateway(phba, BE2_IPV4, &gtway_addr_set);
	if (rt_val) {
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_CONFIG,
			    "BG_%d : Failed to Get Gateway Addr\n");
		return rt_val;
	}

	if (gtway_addr_set.ip_addr.addr[0]) {
		gtway_addr = (uint8_t *)&gtway_addr_set.ip_addr.addr;
		rt_val = mgmt_modify_gateway(phba, gtway_addr, IP_ACTION_DEL,
					     gateway_param->len);
		if (rt_val) {
			beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_CONFIG,
				    "BG_%d : Failed to clear Gateway Addr Set\n");
			return rt_val;
		}
	}

	gtway_addr = (uint8_t *)&gateway_param->value;
	rt_val = mgmt_modify_gateway(phba, gtway_addr, IP_ACTION_ADD,
				     gateway_param->len);

	if (rt_val)
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_CONFIG,
			    "BG_%d : Failed to Set Gateway Addr\n");

	return rt_val;
}