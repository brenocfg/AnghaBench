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
struct qlcnic_info {int capabilities; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  max_mac_filters; int /*<<< orphan*/  max_rx_ques; int /*<<< orphan*/  max_tx_ques; int /*<<< orphan*/  switch_mode; scalar_t__ phys_port; } ;
struct qlcnic_hardware_context {int capabilities; int nic_mode; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  max_mac_filters; int /*<<< orphan*/  max_rx_ques; int /*<<< orphan*/  max_tx_ques; int /*<<< orphan*/  switch_mode; scalar_t__ physical_port; int /*<<< orphan*/  pci_func; } ;
struct qlcnic_adapter {int /*<<< orphan*/  state; struct qlcnic_hardware_context* ahw; } ;

/* Variables and functions */
 int BIT_23 ; 
 int EIO ; 
 void* QLC_83XX_DEFAULT_MODE ; 
 int QLC_83XX_VIRTUAL_NIC_MODE ; 
 int /*<<< orphan*/  __QLCNIC_SRIOV_CAPABLE ; 
 int /*<<< orphan*/  memset (struct qlcnic_info*,int /*<<< orphan*/ ,int) ; 
 int qlcnic_get_nic_info (struct qlcnic_adapter*,struct qlcnic_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qlcnic_83xx_get_nic_configuration(struct qlcnic_adapter *adapter)
{
	int err;
	struct qlcnic_info nic_info;
	struct qlcnic_hardware_context *ahw = adapter->ahw;

	memset(&nic_info, 0, sizeof(struct qlcnic_info));
	err = qlcnic_get_nic_info(adapter, &nic_info, ahw->pci_func);
	if (err)
		return -EIO;

	ahw->physical_port = (u8) nic_info.phys_port;
	ahw->switch_mode = nic_info.switch_mode;
	ahw->max_tx_ques = nic_info.max_tx_ques;
	ahw->max_rx_ques = nic_info.max_rx_ques;
	ahw->capabilities = nic_info.capabilities;
	ahw->max_mac_filters = nic_info.max_mac_filters;
	ahw->max_mtu = nic_info.max_mtu;

	/* VNIC mode is detected by BIT_23 in capabilities. This bit is also
	 * set in case device is SRIOV capable. VNIC and SRIOV are mutually
	 * exclusive. So in case of sriov capable device load driver in
	 * default mode
	 */
	if (test_bit(__QLCNIC_SRIOV_CAPABLE, &adapter->state)) {
		ahw->nic_mode = QLC_83XX_DEFAULT_MODE;
		return ahw->nic_mode;
	}

	if (ahw->capabilities & BIT_23)
		ahw->nic_mode = QLC_83XX_VIRTUAL_NIC_MODE;
	else
		ahw->nic_mode = QLC_83XX_DEFAULT_MODE;

	return ahw->nic_mode;
}