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
struct qlcnic_esw_func_cfg {scalar_t__ pci_func; int op_mode; int mac_override; int promisc_mode; int /*<<< orphan*/  op_type; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  mac_anti_spoof; int /*<<< orphan*/  offload_flags; } ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_2__ {scalar_t__ op_mode; scalar_t__ pci_base0; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_VALID_VLAN (int /*<<< orphan*/ ) ; 
#define  QLCNIC_ADD_VLAN 130 
#define  QLCNIC_DEL_VLAN 129 
 scalar_t__ QLCNIC_DRV_OP_MODE ; 
 scalar_t__ QLCNIC_MAX_PCI_FUNC ; 
 scalar_t__ QLCNIC_MGMT_FUNC ; 
 int QLCNIC_NON_PRIV_FUNC ; 
#define  QLCNIC_PORT_DEFAULTS 128 
 int /*<<< orphan*/  QLCRDX (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_83XX_DRV_OP_MODE ; 
 int QLC_83XX_GET_FUNC_PRIVILEGE (int /*<<< orphan*/ ,scalar_t__) ; 
 int QLC_DEV_GET_DRV (int /*<<< orphan*/ ,scalar_t__) ; 
 int QL_STATUS_INVALID_PARAM ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_is_valid_nic_func (struct qlcnic_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static int validate_esw_config(struct qlcnic_adapter *adapter,
			       struct qlcnic_esw_func_cfg *esw_cfg, int count)
{
	u32 op_mode;
	u8 pci_func;
	int i, ret;

	if (qlcnic_82xx_check(adapter))
		op_mode = readl(adapter->ahw->pci_base0 + QLCNIC_DRV_OP_MODE);
	else
		op_mode = QLCRDX(adapter->ahw, QLC_83XX_DRV_OP_MODE);

	for (i = 0; i < count; i++) {
		pci_func = esw_cfg[i].pci_func;
		if (pci_func >= QLCNIC_MAX_PCI_FUNC)
			return QL_STATUS_INVALID_PARAM;

		if (adapter->ahw->op_mode == QLCNIC_MGMT_FUNC)
			if (qlcnic_is_valid_nic_func(adapter, pci_func) < 0)
				return QL_STATUS_INVALID_PARAM;

		switch (esw_cfg[i].op_mode) {
		case QLCNIC_PORT_DEFAULTS:
			if (qlcnic_82xx_check(adapter)) {
				ret = QLC_DEV_GET_DRV(op_mode, pci_func);
			} else {
				ret = QLC_83XX_GET_FUNC_PRIVILEGE(op_mode,
								  pci_func);
				esw_cfg[i].offload_flags = 0;
			}

			if (ret != QLCNIC_NON_PRIV_FUNC) {
				if (esw_cfg[i].mac_anti_spoof != 0)
					return QL_STATUS_INVALID_PARAM;
				if (esw_cfg[i].mac_override != 1)
					return QL_STATUS_INVALID_PARAM;
				if (esw_cfg[i].promisc_mode != 1)
					return QL_STATUS_INVALID_PARAM;
			}
			break;
		case QLCNIC_ADD_VLAN:
			if (!IS_VALID_VLAN(esw_cfg[i].vlan_id))
				return QL_STATUS_INVALID_PARAM;
			if (!esw_cfg[i].op_type)
				return QL_STATUS_INVALID_PARAM;
			break;
		case QLCNIC_DEL_VLAN:
			if (!esw_cfg[i].op_type)
				return QL_STATUS_INVALID_PARAM;
			break;
		default:
			return QL_STATUS_INVALID_PARAM;
		}
	}

	return 0;
}