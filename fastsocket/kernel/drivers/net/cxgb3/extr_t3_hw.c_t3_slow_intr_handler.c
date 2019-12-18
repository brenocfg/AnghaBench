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
typedef  int u32 ;
struct adapter {int slow_intr_mask; int /*<<< orphan*/  mc5; int /*<<< orphan*/  cm; int /*<<< orphan*/  pmtx; int /*<<< orphan*/  pmrx; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_PL_INT_CAUSE0 ; 
 int F_CIM ; 
 int F_CPL_SWITCH ; 
 int F_MC5A ; 
 int F_MC7_CM ; 
 int F_MC7_PMRX ; 
 int F_MC7_PMTX ; 
 int F_MPS0 ; 
 int F_PCIM0 ; 
 int F_PM1_RX ; 
 int F_PM1_TX ; 
 int F_SGE3 ; 
 int F_T3DBG ; 
 int F_TP1 ; 
 int F_ULP2_RX ; 
 int F_ULP2_TX ; 
 int F_XGMAC0_0 ; 
 int F_XGMAC0_1 ; 
 int /*<<< orphan*/  cim_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  cplsw_intr_handler (struct adapter*) ; 
 scalar_t__ is_pcie (struct adapter*) ; 
 int /*<<< orphan*/  mac_intr_handler (struct adapter*,int) ; 
 int /*<<< orphan*/  mc7_intr_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mps_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  pci_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  pcie_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  pmrx_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  pmtx_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  t3_mc5_intr_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t3_os_ext_intr_handler (struct adapter*) ; 
 int t3_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_sge_err_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tp_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  ulprx_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  ulptx_intr_handler (struct adapter*) ; 

int t3_slow_intr_handler(struct adapter *adapter)
{
	u32 cause = t3_read_reg(adapter, A_PL_INT_CAUSE0);

	cause &= adapter->slow_intr_mask;
	if (!cause)
		return 0;
	if (cause & F_PCIM0) {
		if (is_pcie(adapter))
			pcie_intr_handler(adapter);
		else
			pci_intr_handler(adapter);
	}
	if (cause & F_SGE3)
		t3_sge_err_intr_handler(adapter);
	if (cause & F_MC7_PMRX)
		mc7_intr_handler(&adapter->pmrx);
	if (cause & F_MC7_PMTX)
		mc7_intr_handler(&adapter->pmtx);
	if (cause & F_MC7_CM)
		mc7_intr_handler(&adapter->cm);
	if (cause & F_CIM)
		cim_intr_handler(adapter);
	if (cause & F_TP1)
		tp_intr_handler(adapter);
	if (cause & F_ULP2_RX)
		ulprx_intr_handler(adapter);
	if (cause & F_ULP2_TX)
		ulptx_intr_handler(adapter);
	if (cause & F_PM1_RX)
		pmrx_intr_handler(adapter);
	if (cause & F_PM1_TX)
		pmtx_intr_handler(adapter);
	if (cause & F_CPL_SWITCH)
		cplsw_intr_handler(adapter);
	if (cause & F_MPS0)
		mps_intr_handler(adapter);
	if (cause & F_MC5A)
		t3_mc5_intr_handler(&adapter->mc5);
	if (cause & F_XGMAC0_0)
		mac_intr_handler(adapter, 0);
	if (cause & F_XGMAC0_1)
		mac_intr_handler(adapter, 1);
	if (cause & F_T3DBG)
		t3_os_ext_intr_handler(adapter);

	/* Clear the interrupts just processed. */
	t3_write_reg(adapter, A_PL_INT_CAUSE0, cause);
	t3_read_reg(adapter, A_PL_INT_CAUSE0);	/* flush */
	return 1;
}