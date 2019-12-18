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
typedef  int u8 ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ehea_port {int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  logical_port_id; TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EHEA_BCMC_BROADCAST ; 
 int EHEA_BCMC_UNTAGGED ; 
 int EHEA_BCMC_VLANID_ALL ; 
 int EIO ; 
 int /*<<< orphan*/  H_REG_BCMC ; 
 scalar_t__ H_SUCCESS ; 
 int /*<<< orphan*/  ehea_error (char*,char*) ; 
 scalar_t__ ehea_h_reg_dereg_bcmc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ehea_broadcast_reg_helper(struct ehea_port *port, u32 hcallid)
{
	int ret = 0;
	u64 hret;
	u8 reg_type;

	/* De/Register untagged packets */
	reg_type = EHEA_BCMC_BROADCAST | EHEA_BCMC_UNTAGGED;
	hret = ehea_h_reg_dereg_bcmc(port->adapter->handle,
				     port->logical_port_id,
				     reg_type, port->mac_addr, 0, hcallid);
	if (hret != H_SUCCESS) {
		ehea_error("%sregistering bc address failed (tagged)",
			   hcallid == H_REG_BCMC ? "" : "de");
		ret = -EIO;
		goto out_herr;
	}

	/* De/Register VLAN packets */
	reg_type = EHEA_BCMC_BROADCAST | EHEA_BCMC_VLANID_ALL;
	hret = ehea_h_reg_dereg_bcmc(port->adapter->handle,
				     port->logical_port_id,
				     reg_type, port->mac_addr, 0, hcallid);
	if (hret != H_SUCCESS) {
		ehea_error("%sregistering bc address failed (vlan)",
			   hcallid == H_REG_BCMC ? "" : "de");
		ret = -EIO;
	}
out_herr:
	return ret;
}