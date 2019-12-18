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
struct addr_val_pair {int /*<<< orphan*/  const member_1; scalar_t__ const member_0; } ;
struct TYPE_2__ {scalar_t__ rev; } ;
struct adapter {int slow_intr_mask; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct addr_val_pair const*) ; 
#define  A_CIM_HOST_INT_ENABLE 146 
 int /*<<< orphan*/  A_CPL_INTR_ENABLE ; 
#define  A_MC5_DB_INT_ENABLE 145 
#define  A_MC7_INT_ENABLE 144 
#define  A_MPS_INT_ENABLE 143 
 int /*<<< orphan*/  A_PCIE_INT_ENABLE ; 
 int /*<<< orphan*/  A_PCIX_INT_ENABLE ; 
 int /*<<< orphan*/  A_PL_INT_ENABLE0 ; 
#define  A_PM1_RX_INT_ENABLE 142 
#define  A_PM1_TX_INT_ENABLE 141 
#define  A_SG_INT_ENABLE 140 
 int /*<<< orphan*/  A_T3DBG_INT_ENABLE ; 
 int /*<<< orphan*/  A_TP_INT_ENABLE ; 
#define  A_ULPRX_INT_ENABLE 139 
 int /*<<< orphan*/  A_ULPTX_INT_ENABLE ; 
#define  CIM_INTR_MASK 138 
 int CPLSW_INTR_MASK ; 
 int F_CIM_OVFL_ERROR ; 
 int F_PBL_BOUND_ERR_CH0 ; 
 int F_PBL_BOUND_ERR_CH1 ; 
#define  MC5_INTR_MASK 137 
#define  MC7_CM_BASE_ADDR 136 
#define  MC7_INTR_MASK 135 
#define  MC7_PMRX_BASE_ADDR 134 
#define  MC7_PMTX_BASE_ADDR 133 
#define  MPS_INTR_MASK 132 
 int PCIE_INTR_MASK ; 
 int PCIX_INTR_MASK ; 
 int PL_INTR_MASK ; 
#define  PMRX_INTR_MASK 131 
#define  PMTX_INTR_MASK 130 
#define  SGE_INTR_MASK 129 
 scalar_t__ T3_REV_C ; 
#define  ULPRX_INTR_MASK 128 
 int ULPTX_INTR_MASK ; 
 int calc_gpio_intr (struct adapter*) ; 
 scalar_t__ is_pcie (struct adapter*) ; 
 int /*<<< orphan*/  t3_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t3_write_regs (struct adapter*,struct addr_val_pair const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void t3_intr_enable(struct adapter *adapter)
{
	static const struct addr_val_pair intr_en_avp[] = {
		{A_SG_INT_ENABLE, SGE_INTR_MASK},
		{A_MC7_INT_ENABLE, MC7_INTR_MASK},
		{A_MC7_INT_ENABLE - MC7_PMRX_BASE_ADDR + MC7_PMTX_BASE_ADDR,
		 MC7_INTR_MASK},
		{A_MC7_INT_ENABLE - MC7_PMRX_BASE_ADDR + MC7_CM_BASE_ADDR,
		 MC7_INTR_MASK},
		{A_MC5_DB_INT_ENABLE, MC5_INTR_MASK},
		{A_ULPRX_INT_ENABLE, ULPRX_INTR_MASK},
		{A_PM1_TX_INT_ENABLE, PMTX_INTR_MASK},
		{A_PM1_RX_INT_ENABLE, PMRX_INTR_MASK},
		{A_CIM_HOST_INT_ENABLE, CIM_INTR_MASK},
		{A_MPS_INT_ENABLE, MPS_INTR_MASK},
	};

	adapter->slow_intr_mask = PL_INTR_MASK;

	t3_write_regs(adapter, intr_en_avp, ARRAY_SIZE(intr_en_avp), 0);
	t3_write_reg(adapter, A_TP_INT_ENABLE,
		     adapter->params.rev >= T3_REV_C ? 0x2bfffff : 0x3bfffff);

	if (adapter->params.rev > 0) {
		t3_write_reg(adapter, A_CPL_INTR_ENABLE,
			     CPLSW_INTR_MASK | F_CIM_OVFL_ERROR);
		t3_write_reg(adapter, A_ULPTX_INT_ENABLE,
			     ULPTX_INTR_MASK | F_PBL_BOUND_ERR_CH0 |
			     F_PBL_BOUND_ERR_CH1);
	} else {
		t3_write_reg(adapter, A_CPL_INTR_ENABLE, CPLSW_INTR_MASK);
		t3_write_reg(adapter, A_ULPTX_INT_ENABLE, ULPTX_INTR_MASK);
	}

	t3_write_reg(adapter, A_T3DBG_INT_ENABLE, calc_gpio_intr(adapter));

	if (is_pcie(adapter))
		t3_write_reg(adapter, A_PCIE_INT_ENABLE, PCIE_INTR_MASK);
	else
		t3_write_reg(adapter, A_PCIX_INT_ENABLE, PCIX_INTR_MASK);
	t3_write_reg(adapter, A_PL_INT_ENABLE0, adapter->slow_intr_mask);
	t3_read_reg(adapter, A_PL_INT_ENABLE0);	/* flush */
}