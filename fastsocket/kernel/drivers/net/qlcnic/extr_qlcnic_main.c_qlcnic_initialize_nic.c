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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_info {int capabilities; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  max_mac_filters; int /*<<< orphan*/  max_rx_ques; int /*<<< orphan*/  max_tx_ques; int /*<<< orphan*/  switch_mode; scalar_t__ phys_port; } ;
struct qlcnic_adapter {int /*<<< orphan*/  flags; TYPE_1__* ahw; } ;
struct TYPE_2__ {int capabilities; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  max_mac_filters; int /*<<< orphan*/  capabilities2; int /*<<< orphan*/  max_rx_ques; int /*<<< orphan*/  max_tx_ques; int /*<<< orphan*/  switch_mode; scalar_t__ physical_port; int /*<<< orphan*/  pci_func; } ;

/* Variables and functions */
 int BIT_6 ; 
 int /*<<< orphan*/  CRB_FW_CAPABILITIES_2 ; 
 int /*<<< orphan*/  QLCNIC_ESWITCH_ENABLED ; 
 int QLCNIC_FW_CAPABILITY_MORE_CAPS ; 
 int /*<<< orphan*/  QLCRD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qlcnic_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int qlcnic_get_nic_info (struct qlcnic_adapter*,struct qlcnic_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qlcnic_initialize_nic(struct qlcnic_adapter *adapter)
{
	int err;
	struct qlcnic_info nic_info;

	memset(&nic_info, 0, sizeof(struct qlcnic_info));
	err = qlcnic_get_nic_info(adapter, &nic_info, adapter->ahw->pci_func);
	if (err)
		return err;

	adapter->ahw->physical_port = (u8)nic_info.phys_port;
	adapter->ahw->switch_mode = nic_info.switch_mode;
	adapter->ahw->max_tx_ques = nic_info.max_tx_ques;
	adapter->ahw->max_rx_ques = nic_info.max_rx_ques;
	adapter->ahw->capabilities = nic_info.capabilities;

	if (adapter->ahw->capabilities & QLCNIC_FW_CAPABILITY_MORE_CAPS) {
		u32 temp;
		temp = QLCRD32(adapter, CRB_FW_CAPABILITIES_2);
		adapter->ahw->capabilities2 = temp;
	}
	adapter->ahw->max_mac_filters = nic_info.max_mac_filters;
	adapter->ahw->max_mtu = nic_info.max_mtu;

	/* Disable NPAR for 83XX */
	if (qlcnic_83xx_check(adapter))
		return err;

	if (adapter->ahw->capabilities & BIT_6)
		adapter->flags |= QLCNIC_ESWITCH_ENABLED;
	else
		adapter->flags &= ~QLCNIC_ESWITCH_ENABLED;

	return err;
}