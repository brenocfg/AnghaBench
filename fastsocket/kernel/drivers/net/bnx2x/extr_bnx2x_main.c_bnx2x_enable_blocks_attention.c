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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ BRB1_REG_BRB1_INT_MASK ; 
 scalar_t__ CCM_REG_CCM_INT_MASK ; 
 scalar_t__ CDU_REG_CDU_INT_MASK ; 
 scalar_t__ CFC_REG_CFC_INT_MASK ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bnx2x*) ; 
 scalar_t__ CSDM_REG_CSDM_INT_MASK_0 ; 
 scalar_t__ CSDM_REG_CSDM_INT_MASK_1 ; 
 scalar_t__ DMAE_REG_DMAE_INT_MASK ; 
 scalar_t__ DORQ_REG_DORQ_INT_MASK ; 
 scalar_t__ GRCBASE_UPB ; 
 scalar_t__ PBF_REG_PBF_INT_MASK ; 
 scalar_t__ PB_REG_PB_INT_MASK ; 
 int PXP2_PXP2_INT_MASK_0_REG_PGL_CPL_AFT ; 
 int PXP2_PXP2_INT_MASK_0_REG_PGL_CPL_OF ; 
 int PXP2_PXP2_INT_MASK_0_REG_PGL_PCIE_ATTN ; 
 int PXP2_PXP2_INT_MASK_0_REG_PGL_READ_BLOCKED ; 
 int PXP2_PXP2_INT_MASK_0_REG_PGL_WRITE_BLOCKED ; 
 scalar_t__ PXP2_REG_PXP2_INT_MASK_0 ; 
 scalar_t__ PXP_REG_PXP_INT_MASK_0 ; 
 scalar_t__ PXP_REG_PXP_INT_MASK_1 ; 
 scalar_t__ QM_REG_QM_INT_MASK ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int) ; 
 scalar_t__ TCM_REG_TCM_INT_MASK ; 
 scalar_t__ TM_REG_TM_INT_MASK ; 
 scalar_t__ TSDM_REG_TSDM_INT_MASK_0 ; 
 scalar_t__ TSDM_REG_TSDM_INT_MASK_1 ; 
 scalar_t__ TSEM_REG_TSEM_INT_MASK_1 ; 
 scalar_t__ UCM_REG_UCM_INT_MASK ; 
 scalar_t__ USDM_REG_USDM_INT_MASK_0 ; 
 scalar_t__ USDM_REG_USDM_INT_MASK_1 ; 
 scalar_t__ XCM_REG_XCM_INT_MASK ; 
 scalar_t__ XSDM_REG_XSDM_INT_MASK_0 ; 
 scalar_t__ XSDM_REG_XSDM_INT_MASK_1 ; 

__attribute__((used)) static void bnx2x_enable_blocks_attention(struct bnx2x *bp)
{
	u32 val;

	REG_WR(bp, PXP_REG_PXP_INT_MASK_0, 0);
	if (!CHIP_IS_E1x(bp))
		REG_WR(bp, PXP_REG_PXP_INT_MASK_1, 0x40);
	else
		REG_WR(bp, PXP_REG_PXP_INT_MASK_1, 0);
	REG_WR(bp, DORQ_REG_DORQ_INT_MASK, 0);
	REG_WR(bp, CFC_REG_CFC_INT_MASK, 0);
	/*
	 * mask read length error interrupts in brb for parser
	 * (parsing unit and 'checksum and crc' unit)
	 * these errors are legal (PU reads fixed length and CAC can cause
	 * read length error on truncated packets)
	 */
	REG_WR(bp, BRB1_REG_BRB1_INT_MASK, 0xFC00);
	REG_WR(bp, QM_REG_QM_INT_MASK, 0);
	REG_WR(bp, TM_REG_TM_INT_MASK, 0);
	REG_WR(bp, XSDM_REG_XSDM_INT_MASK_0, 0);
	REG_WR(bp, XSDM_REG_XSDM_INT_MASK_1, 0);
	REG_WR(bp, XCM_REG_XCM_INT_MASK, 0);
/*	REG_WR(bp, XSEM_REG_XSEM_INT_MASK_0, 0); */
/*	REG_WR(bp, XSEM_REG_XSEM_INT_MASK_1, 0); */
	REG_WR(bp, USDM_REG_USDM_INT_MASK_0, 0);
	REG_WR(bp, USDM_REG_USDM_INT_MASK_1, 0);
	REG_WR(bp, UCM_REG_UCM_INT_MASK, 0);
/*	REG_WR(bp, USEM_REG_USEM_INT_MASK_0, 0); */
/*	REG_WR(bp, USEM_REG_USEM_INT_MASK_1, 0); */
	REG_WR(bp, GRCBASE_UPB + PB_REG_PB_INT_MASK, 0);
	REG_WR(bp, CSDM_REG_CSDM_INT_MASK_0, 0);
	REG_WR(bp, CSDM_REG_CSDM_INT_MASK_1, 0);
	REG_WR(bp, CCM_REG_CCM_INT_MASK, 0);
/*	REG_WR(bp, CSEM_REG_CSEM_INT_MASK_0, 0); */
/*	REG_WR(bp, CSEM_REG_CSEM_INT_MASK_1, 0); */

	val = PXP2_PXP2_INT_MASK_0_REG_PGL_CPL_AFT  |
		PXP2_PXP2_INT_MASK_0_REG_PGL_CPL_OF |
		PXP2_PXP2_INT_MASK_0_REG_PGL_PCIE_ATTN;
	if (!CHIP_IS_E1x(bp))
		val |= PXP2_PXP2_INT_MASK_0_REG_PGL_READ_BLOCKED |
			PXP2_PXP2_INT_MASK_0_REG_PGL_WRITE_BLOCKED;
	REG_WR(bp, PXP2_REG_PXP2_INT_MASK_0, val);

	REG_WR(bp, TSDM_REG_TSDM_INT_MASK_0, 0);
	REG_WR(bp, TSDM_REG_TSDM_INT_MASK_1, 0);
	REG_WR(bp, TCM_REG_TCM_INT_MASK, 0);
/*	REG_WR(bp, TSEM_REG_TSEM_INT_MASK_0, 0); */

	if (!CHIP_IS_E1x(bp))
		/* enable VFC attentions: bits 11 and 12, bits 31:13 reserved */
		REG_WR(bp, TSEM_REG_TSEM_INT_MASK_1, 0x07ff);

	REG_WR(bp, CDU_REG_CDU_INT_MASK, 0);
	REG_WR(bp, DMAE_REG_DMAE_INT_MASK, 0);
/*	REG_WR(bp, MISC_REG_MISC_INT_MASK, 0); */
	REG_WR(bp, PBF_REG_PBF_INT_MASK, 0x18);		/* bit 3,4 masked */
}