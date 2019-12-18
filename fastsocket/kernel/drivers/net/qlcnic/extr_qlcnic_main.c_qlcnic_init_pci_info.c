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
typedef  int u16 ;
struct qlcnic_pci_info {int id; int active; scalar_t__ type; int pci_func; int phy_port; int /*<<< orphan*/  flags; int /*<<< orphan*/  tx_max_bw; int /*<<< orphan*/  max_bw; int /*<<< orphan*/  tx_min_bw; int /*<<< orphan*/  min_bw; scalar_t__ default_port; } ;
struct qlcnic_npar_info {int dummy; } ;
struct qlcnic_eswitch {int dummy; } ;
struct qlcnic_adapter {struct qlcnic_pci_info* npars; struct qlcnic_pci_info* eswitch; TYPE_1__* ahw; } ;
struct TYPE_2__ {int act_pci_func; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QLCNIC_MAX_PCI_FUNC ; 
 int QLCNIC_NIU_MAX_XG_PORTS ; 
 int /*<<< orphan*/  QLCNIC_SWITCH_ENABLE ; 
 scalar_t__ QLCNIC_TYPE_NIC ; 
 int QL_STATUS_INVALID_PARAM ; 
 struct qlcnic_pci_info* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qlcnic_pci_info*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_enable_eswitch (struct qlcnic_adapter*,int,int) ; 
 int qlcnic_get_pci_info (struct qlcnic_adapter*,struct qlcnic_pci_info*) ; 

int qlcnic_init_pci_info(struct qlcnic_adapter *adapter)
{
	struct qlcnic_pci_info *pci_info;
	int i, ret = 0, j = 0;
	u16 act_pci_func;
	u8 pfn;

	pci_info = kcalloc(QLCNIC_MAX_PCI_FUNC, sizeof(*pci_info), GFP_KERNEL);
	if (!pci_info)
		return -ENOMEM;

	ret = qlcnic_get_pci_info(adapter, pci_info);
	if (ret)
		goto err_pci_info;

	act_pci_func = adapter->ahw->act_pci_func;

	adapter->npars = kzalloc(sizeof(struct qlcnic_npar_info) *
				 act_pci_func, GFP_KERNEL);
	if (!adapter->npars) {
		ret = -ENOMEM;
		goto err_pci_info;
	}

	adapter->eswitch = kzalloc(sizeof(struct qlcnic_eswitch) *
				QLCNIC_NIU_MAX_XG_PORTS, GFP_KERNEL);
	if (!adapter->eswitch) {
		ret = -ENOMEM;
		goto err_npars;
	}

	for (i = 0; i < QLCNIC_MAX_PCI_FUNC; i++) {
		pfn = pci_info[i].id;

		if (pfn >= QLCNIC_MAX_PCI_FUNC) {
			ret = QL_STATUS_INVALID_PARAM;
			goto err_eswitch;
		}

		if (!pci_info[i].active ||
		    (pci_info[i].type != QLCNIC_TYPE_NIC))
			continue;

		adapter->npars[j].pci_func = pfn;
		adapter->npars[j].active = (u8)pci_info[i].active;
		adapter->npars[j].type = (u8)pci_info[i].type;
		adapter->npars[j].phy_port = (u8)pci_info[i].default_port;
		adapter->npars[j].min_bw = pci_info[i].tx_min_bw;
		adapter->npars[j].max_bw = pci_info[i].tx_max_bw;
		j++;
	}

	for (i = 0; i < QLCNIC_NIU_MAX_XG_PORTS; i++) {
		adapter->eswitch[i].flags |= QLCNIC_SWITCH_ENABLE;
		if (qlcnic_83xx_check(adapter))
			qlcnic_enable_eswitch(adapter, i, 1);
	}

	kfree(pci_info);
	return 0;

err_eswitch:
	kfree(adapter->eswitch);
	adapter->eswitch = NULL;
err_npars:
	kfree(adapter->npars);
	adapter->npars = NULL;
err_pci_info:
	kfree(pci_info);

	return ret;
}