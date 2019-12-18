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
struct qlcnic_pci_info {int dummy; } ;
struct qlcnic_adapter {int flags; TYPE_1__* ahw; } ;
struct TYPE_2__ {int port_type; scalar_t__ op_mode; int /*<<< orphan*/  act_pci_func; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QLCNIC_ESWITCH_ENABLED ; 
#define  QLCNIC_GBE 129 
 int /*<<< orphan*/  QLCNIC_MAX_PCI_FUNC ; 
 scalar_t__ QLCNIC_MGMT_FUNC ; 
 int /*<<< orphan*/  QLCNIC_NIU_MAX_GBE_PORTS ; 
 int /*<<< orphan*/  QLCNIC_NIU_MAX_XG_PORTS ; 
#define  QLCNIC_XGBE 128 
 struct qlcnic_pci_info* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qlcnic_pci_info*) ; 
 int qlcnic_get_pci_info (struct qlcnic_adapter*,struct qlcnic_pci_info*) ; 

__attribute__((used)) static int qlcnic_get_act_pci_func(struct qlcnic_adapter *adapter)
{
	struct qlcnic_pci_info *pci_info;
	int ret;

	if (!(adapter->flags & QLCNIC_ESWITCH_ENABLED)) {
		switch (adapter->ahw->port_type) {
		case QLCNIC_GBE:
			adapter->ahw->act_pci_func = QLCNIC_NIU_MAX_GBE_PORTS;
			break;
		case QLCNIC_XGBE:
			adapter->ahw->act_pci_func = QLCNIC_NIU_MAX_XG_PORTS;
			break;
		}
		return 0;
	}

	if (adapter->ahw->op_mode == QLCNIC_MGMT_FUNC)
		return 0;

	pci_info = kcalloc(QLCNIC_MAX_PCI_FUNC, sizeof(*pci_info), GFP_KERNEL);
	if (!pci_info)
		return -ENOMEM;

	ret = qlcnic_get_pci_info(adapter, pci_info);
	kfree(pci_info);
	return ret;
}