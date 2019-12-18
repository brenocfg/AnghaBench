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
struct adapter {int dummy; } ;

/* Variables and functions */
 int CIM ; 
 int CPL_SWITCH ; 
 int EDC0 ; 
 int EDC1 ; 
 int GLBL_INTR_MASK ; 
 int LE ; 
 int MA ; 
 int MC ; 
 int /*<<< orphan*/  MEM_EDC0 ; 
 int /*<<< orphan*/  MEM_EDC1 ; 
 int /*<<< orphan*/  MEM_MC ; 
 int MPS ; 
 int NCSI ; 
 int PCIE ; 
 int PL ; 
 int /*<<< orphan*/  PL_INT_CAUSE ; 
 int PM_RX ; 
 int PM_TX ; 
 int SGE ; 
 int SMB ; 
 int TP ; 
 int ULP_RX ; 
 int ULP_TX ; 
 int XGMAC0 ; 
 int XGMAC1 ; 
 int XGMAC_KR0 ; 
 int XGMAC_KR1 ; 
 int /*<<< orphan*/  cim_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  cplsw_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  le_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  ma_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  mem_intr_handler (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  ncsi_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  pcie_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  pl_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  pmrx_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  pmtx_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  sge_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  smb_intr_handler (struct adapter*) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tp_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  ulprx_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  ulptx_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  xgmac_intr_handler (struct adapter*,int) ; 

int t4_slow_intr_handler(struct adapter *adapter)
{
	u32 cause = t4_read_reg(adapter, PL_INT_CAUSE);

	if (!(cause & GLBL_INTR_MASK))
		return 0;
	if (cause & CIM)
		cim_intr_handler(adapter);
	if (cause & MPS)
		mps_intr_handler(adapter);
	if (cause & NCSI)
		ncsi_intr_handler(adapter);
	if (cause & PL)
		pl_intr_handler(adapter);
	if (cause & SMB)
		smb_intr_handler(adapter);
	if (cause & XGMAC0)
		xgmac_intr_handler(adapter, 0);
	if (cause & XGMAC1)
		xgmac_intr_handler(adapter, 1);
	if (cause & XGMAC_KR0)
		xgmac_intr_handler(adapter, 2);
	if (cause & XGMAC_KR1)
		xgmac_intr_handler(adapter, 3);
	if (cause & PCIE)
		pcie_intr_handler(adapter);
	if (cause & MC)
		mem_intr_handler(adapter, MEM_MC);
	if (cause & EDC0)
		mem_intr_handler(adapter, MEM_EDC0);
	if (cause & EDC1)
		mem_intr_handler(adapter, MEM_EDC1);
	if (cause & LE)
		le_intr_handler(adapter);
	if (cause & TP)
		tp_intr_handler(adapter);
	if (cause & MA)
		ma_intr_handler(adapter);
	if (cause & PM_TX)
		pmtx_intr_handler(adapter);
	if (cause & PM_RX)
		pmrx_intr_handler(adapter);
	if (cause & ULP_RX)
		ulprx_intr_handler(adapter);
	if (cause & CPL_SWITCH)
		cplsw_intr_handler(adapter);
	if (cause & SGE)
		sge_intr_handler(adapter);
	if (cause & ULP_TX)
		ulptx_intr_handler(adapter);

	/* Clear the interrupts just processed for which we are the master. */
	t4_write_reg(adapter, PL_INT_CAUSE, cause & GLBL_INTR_MASK);
	(void) t4_read_reg(adapter, PL_INT_CAUSE); /* flush */
	return 1;
}