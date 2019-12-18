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
typedef  int u32 ;
struct qlcnic_hardware_context {int capabilities; } ;
struct qlcnic_adapter {TYPE_1__* pdev; struct qlcnic_hardware_context* ahw; } ;
struct TYPE_2__ {scalar_t__ device; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_QLOGIC_QLE824X ; 
 int QLCNIC_FW_CAPABILITY_FVLANTX ; 

__attribute__((used)) static u32 qlcnic_vlan_tx_check(struct qlcnic_adapter *adapter)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;

	if (adapter->pdev->device == PCI_DEVICE_ID_QLOGIC_QLE824X)
		return ahw->capabilities & QLCNIC_FW_CAPABILITY_FVLANTX;
	else
		return 1;
}