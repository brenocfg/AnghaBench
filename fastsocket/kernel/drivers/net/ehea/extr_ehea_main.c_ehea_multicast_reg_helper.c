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
struct ehea_port {int /*<<< orphan*/  logical_port_id; TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EHEA_BCMC_MULTICAST ; 
 int EHEA_BCMC_SCOPE_ALL ; 
 int EHEA_BCMC_UNTAGGED ; 
 int EHEA_BCMC_VLANID_ALL ; 
 scalar_t__ ehea_h_reg_dereg_bcmc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 ehea_multicast_reg_helper(struct ehea_port *port, u64 mc_mac_addr,
				     u32 hcallid)
{
	u64 hret;
	u8 reg_type;

	reg_type = EHEA_BCMC_MULTICAST | EHEA_BCMC_UNTAGGED;
	if (mc_mac_addr == 0)
		reg_type |= EHEA_BCMC_SCOPE_ALL;

	hret = ehea_h_reg_dereg_bcmc(port->adapter->handle,
				     port->logical_port_id,
				     reg_type, mc_mac_addr, 0, hcallid);
	if (hret)
		goto out;

	reg_type = EHEA_BCMC_MULTICAST | EHEA_BCMC_VLANID_ALL;
	if (mc_mac_addr == 0)
		reg_type |= EHEA_BCMC_SCOPE_ALL;

	hret = ehea_h_reg_dereg_bcmc(port->adapter->handle,
				     port->logical_port_id,
				     reg_type, mc_mac_addr, 0, hcallid);
out:
	return hret;
}