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
struct bnx2x {int flags; int mf_mode; scalar_t__ path_has_ovlan; TYPE_1__* dev; int /*<<< orphan*/  qm_cid_count; } ;
struct TYPE_2__ {int mtu; } ;

/* Variables and functions */
 int AEU_INPUTS_ATTN_BITS_SPIO5 ; 
 int /*<<< orphan*/  BLOCK_ATC ; 
 int /*<<< orphan*/  BLOCK_BRB1 ; 
 int /*<<< orphan*/  BLOCK_CCM ; 
 int /*<<< orphan*/  BLOCK_CDU ; 
 int /*<<< orphan*/  BLOCK_CFC ; 
 int /*<<< orphan*/  BLOCK_CSDM ; 
 int /*<<< orphan*/  BLOCK_CSEM ; 
 int /*<<< orphan*/  BLOCK_DMAE ; 
 int /*<<< orphan*/  BLOCK_DORQ ; 
 int /*<<< orphan*/  BLOCK_HC ; 
 int /*<<< orphan*/  BLOCK_IGU ; 
 int /*<<< orphan*/  BLOCK_MISC ; 
 int /*<<< orphan*/  BLOCK_MISC_AEU ; 
 int /*<<< orphan*/  BLOCK_NIG ; 
 int /*<<< orphan*/  BLOCK_PBF ; 
 int /*<<< orphan*/  BLOCK_PGLUE_B ; 
 int /*<<< orphan*/  BLOCK_PRS ; 
 int /*<<< orphan*/  BLOCK_PXP ; 
 int /*<<< orphan*/  BLOCK_PXP2 ; 
 int /*<<< orphan*/  BLOCK_QM ; 
 int /*<<< orphan*/  BLOCK_SRC ; 
 int /*<<< orphan*/  BLOCK_TCM ; 
 int /*<<< orphan*/  BLOCK_TM ; 
 int /*<<< orphan*/  BLOCK_TSDM ; 
 int /*<<< orphan*/  BLOCK_TSEM ; 
 int /*<<< orphan*/  BLOCK_UCM ; 
 int /*<<< orphan*/  BLOCK_UPB ; 
 int /*<<< orphan*/  BLOCK_USDM ; 
 int /*<<< orphan*/  BLOCK_USEM ; 
 int /*<<< orphan*/  BLOCK_XCM ; 
 int /*<<< orphan*/  BLOCK_XPB ; 
 int /*<<< orphan*/  BLOCK_XSDM ; 
 int /*<<< orphan*/  BLOCK_XSEM ; 
 int BP_PORT (struct bnx2x*) ; 
 int BRB1_REG_MAC_GUARANTIED_0 ; 
 int BRB1_REG_MAC_GUARANTIED_1 ; 
 int BRB1_REG_PAUSE_HIGH_THRESHOLD_0 ; 
 int BRB1_REG_PAUSE_LOW_THRESHOLD_0 ; 
 scalar_t__ CHIP_IS_E1 (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E1H (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E1x (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E3 (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E3B0 (struct bnx2x*) ; 
 scalar_t__ CHIP_MODE_IS_4_PORT (struct bnx2x*) ; 
 scalar_t__ CNIC_SUPPORT (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int HC_REG_LEADING_EDGE_0 ; 
 int HC_REG_TRAILING_EDGE_0 ; 
 int /*<<< orphan*/  INITOP_SET ; 
 int IS_MF (struct bnx2x*) ; 
 scalar_t__ IS_MF_AFEX (struct bnx2x*) ; 
 scalar_t__ IS_MF_SD (struct bnx2x*) ; 
 int MISC_REG_AEU_ENABLE1_FUNC_0_OUT_0 ; 
 int MISC_REG_AEU_ENABLE1_FUNC_1_OUT_0 ; 
 int MISC_REG_AEU_MASK_ATTN_FUNC_0 ; 
 int MISC_REG_SPIO_EVENT_EN ; 
 int MISC_SPIO_SPIO5 ; 
#define  MULTI_FUNCTION_AFEX 130 
#define  MULTI_FUNCTION_SD 129 
#define  MULTI_FUNCTION_SI 128 
 int /*<<< orphan*/  NETIF_MSG_HW ; 
 int NIG_REG_LLFC_ENABLE_0 ; 
 int NIG_REG_LLFC_OUT_EN_0 ; 
 int NIG_REG_LLH0_BRB1_DRV_MASK_MF ; 
 int NIG_REG_LLH0_CLS_TYPE ; 
 int NIG_REG_LLH1_CLS_TYPE ; 
 int NIG_REG_LLH1_MF_MODE ; 
 int NIG_REG_LLH_MF_MODE ; 
 int NIG_REG_MASK_INTERRUPT_PORT0 ; 
 int NIG_REG_P0_HDRS_AFTER_BASIC ; 
 int NIG_REG_P1_HDRS_AFTER_BASIC ; 
 int NIG_REG_PAUSE_ENABLE_0 ; 
 int NIG_REG_XGXS_SERDES0_MODE_SEL ; 
 int ONE_PORT_FLAG ; 
 int PBF_REG_INIT_P0 ; 
 int PBF_REG_P0_ARB_THRSH ; 
 int PBF_REG_P0_INIT_CRD ; 
 int PBF_REG_P0_PAUSE_ENABLE ; 
 int PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER ; 
 int PHASE_PORT0 ; 
 int PHASE_PORT1 ; 
 int PRS_REG_HDRS_AFTER_BASIC_PORT_0 ; 
 int PRS_REG_HDRS_AFTER_BASIC_PORT_1 ; 
 int PRS_REG_HDRS_AFTER_TAG_0_PORT_0 ; 
 int PRS_REG_HDRS_AFTER_TAG_0_PORT_1 ; 
 int PRS_REG_MUST_HAVE_HDRS_PORT_0 ; 
 int PRS_REG_MUST_HAVE_HDRS_PORT_1 ; 
 int REG_RD (struct bnx2x*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int,int) ; 
 int TM_REG_LIN0_MAX_ACTIVE_CID ; 
 int TM_REG_LIN0_SCAN_TIME ; 
 int /*<<< orphan*/  bnx2x_init_block (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_qm_init_cid_count (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int bnx2x_init_hw_port(struct bnx2x *bp)
{
	int port = BP_PORT(bp);
	int init_phase = port ? PHASE_PORT1 : PHASE_PORT0;
	u32 low, high;
	u32 val;

	DP(NETIF_MSG_HW, "starting port init  port %d\n", port);

	REG_WR(bp, NIG_REG_MASK_INTERRUPT_PORT0 + port*4, 0);

	bnx2x_init_block(bp, BLOCK_MISC, init_phase);
	bnx2x_init_block(bp, BLOCK_PXP, init_phase);
	bnx2x_init_block(bp, BLOCK_PXP2, init_phase);

	/* Timers bug workaround: disables the pf_master bit in pglue at
	 * common phase, we need to enable it here before any dmae access are
	 * attempted. Therefore we manually added the enable-master to the
	 * port phase (it also happens in the function phase)
	 */
	if (!CHIP_IS_E1x(bp))
		REG_WR(bp, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER, 1);

	bnx2x_init_block(bp, BLOCK_ATC, init_phase);
	bnx2x_init_block(bp, BLOCK_DMAE, init_phase);
	bnx2x_init_block(bp, BLOCK_PGLUE_B, init_phase);
	bnx2x_init_block(bp, BLOCK_QM, init_phase);

	bnx2x_init_block(bp, BLOCK_TCM, init_phase);
	bnx2x_init_block(bp, BLOCK_UCM, init_phase);
	bnx2x_init_block(bp, BLOCK_CCM, init_phase);
	bnx2x_init_block(bp, BLOCK_XCM, init_phase);

	/* QM cid (connection) count */
	bnx2x_qm_init_cid_count(bp, bp->qm_cid_count, INITOP_SET);

	if (CNIC_SUPPORT(bp)) {
		bnx2x_init_block(bp, BLOCK_TM, init_phase);
		REG_WR(bp, TM_REG_LIN0_SCAN_TIME + port*4, 20);
		REG_WR(bp, TM_REG_LIN0_MAX_ACTIVE_CID + port*4, 31);
	}

	bnx2x_init_block(bp, BLOCK_DORQ, init_phase);

	bnx2x_init_block(bp, BLOCK_BRB1, init_phase);

	if (CHIP_IS_E1(bp) || CHIP_IS_E1H(bp)) {

		if (IS_MF(bp))
			low = ((bp->flags & ONE_PORT_FLAG) ? 160 : 246);
		else if (bp->dev->mtu > 4096) {
			if (bp->flags & ONE_PORT_FLAG)
				low = 160;
			else {
				val = bp->dev->mtu;
				/* (24*1024 + val*4)/256 */
				low = 96 + (val/64) +
						((val % 64) ? 1 : 0);
			}
		} else
			low = ((bp->flags & ONE_PORT_FLAG) ? 80 : 160);
		high = low + 56;	/* 14*1024/256 */
		REG_WR(bp, BRB1_REG_PAUSE_LOW_THRESHOLD_0 + port*4, low);
		REG_WR(bp, BRB1_REG_PAUSE_HIGH_THRESHOLD_0 + port*4, high);
	}

	if (CHIP_MODE_IS_4_PORT(bp))
		REG_WR(bp, (BP_PORT(bp) ?
			    BRB1_REG_MAC_GUARANTIED_1 :
			    BRB1_REG_MAC_GUARANTIED_0), 40);

	bnx2x_init_block(bp, BLOCK_PRS, init_phase);
	if (CHIP_IS_E3B0(bp)) {
		if (IS_MF_AFEX(bp)) {
			/* configure headers for AFEX mode */
			REG_WR(bp, BP_PORT(bp) ?
			       PRS_REG_HDRS_AFTER_BASIC_PORT_1 :
			       PRS_REG_HDRS_AFTER_BASIC_PORT_0, 0xE);
			REG_WR(bp, BP_PORT(bp) ?
			       PRS_REG_HDRS_AFTER_TAG_0_PORT_1 :
			       PRS_REG_HDRS_AFTER_TAG_0_PORT_0, 0x6);
			REG_WR(bp, BP_PORT(bp) ?
			       PRS_REG_MUST_HAVE_HDRS_PORT_1 :
			       PRS_REG_MUST_HAVE_HDRS_PORT_0, 0xA);
		} else {
			/* Ovlan exists only if we are in multi-function +
			 * switch-dependent mode, in switch-independent there
			 * is no ovlan headers
			 */
			REG_WR(bp, BP_PORT(bp) ?
			       PRS_REG_HDRS_AFTER_BASIC_PORT_1 :
			       PRS_REG_HDRS_AFTER_BASIC_PORT_0,
			       (bp->path_has_ovlan ? 7 : 6));
		}
	}

	bnx2x_init_block(bp, BLOCK_TSDM, init_phase);
	bnx2x_init_block(bp, BLOCK_CSDM, init_phase);
	bnx2x_init_block(bp, BLOCK_USDM, init_phase);
	bnx2x_init_block(bp, BLOCK_XSDM, init_phase);

	bnx2x_init_block(bp, BLOCK_TSEM, init_phase);
	bnx2x_init_block(bp, BLOCK_USEM, init_phase);
	bnx2x_init_block(bp, BLOCK_CSEM, init_phase);
	bnx2x_init_block(bp, BLOCK_XSEM, init_phase);

	bnx2x_init_block(bp, BLOCK_UPB, init_phase);
	bnx2x_init_block(bp, BLOCK_XPB, init_phase);

	bnx2x_init_block(bp, BLOCK_PBF, init_phase);

	if (CHIP_IS_E1x(bp)) {
		/* configure PBF to work without PAUSE mtu 9000 */
		REG_WR(bp, PBF_REG_P0_PAUSE_ENABLE + port*4, 0);

		/* update threshold */
		REG_WR(bp, PBF_REG_P0_ARB_THRSH + port*4, (9040/16));
		/* update init credit */
		REG_WR(bp, PBF_REG_P0_INIT_CRD + port*4, (9040/16) + 553 - 22);

		/* probe changes */
		REG_WR(bp, PBF_REG_INIT_P0 + port*4, 1);
		udelay(50);
		REG_WR(bp, PBF_REG_INIT_P0 + port*4, 0);
	}

	if (CNIC_SUPPORT(bp))
		bnx2x_init_block(bp, BLOCK_SRC, init_phase);

	bnx2x_init_block(bp, BLOCK_CDU, init_phase);
	bnx2x_init_block(bp, BLOCK_CFC, init_phase);

	if (CHIP_IS_E1(bp)) {
		REG_WR(bp, HC_REG_LEADING_EDGE_0 + port*8, 0);
		REG_WR(bp, HC_REG_TRAILING_EDGE_0 + port*8, 0);
	}
	bnx2x_init_block(bp, BLOCK_HC, init_phase);

	bnx2x_init_block(bp, BLOCK_IGU, init_phase);

	bnx2x_init_block(bp, BLOCK_MISC_AEU, init_phase);
	/* init aeu_mask_attn_func_0/1:
	 *  - SF mode: bits 3-7 are masked. Only bits 0-2 are in use
	 *  - MF mode: bit 3 is masked. Bits 0-2 are in use as in SF
	 *             bits 4-7 are used for "per vn group attention" */
	val = IS_MF(bp) ? 0xF7 : 0x7;
	/* Enable DCBX attention for all but E1 */
	val |= CHIP_IS_E1(bp) ? 0 : 0x10;
	REG_WR(bp, MISC_REG_AEU_MASK_ATTN_FUNC_0 + port*4, val);

	bnx2x_init_block(bp, BLOCK_NIG, init_phase);

	if (!CHIP_IS_E1x(bp)) {
		/* Bit-map indicating which L2 hdrs may appear after the
		 * basic Ethernet header
		 */
		if (IS_MF_AFEX(bp))
			REG_WR(bp, BP_PORT(bp) ?
			       NIG_REG_P1_HDRS_AFTER_BASIC :
			       NIG_REG_P0_HDRS_AFTER_BASIC, 0xE);
		else
			REG_WR(bp, BP_PORT(bp) ?
			       NIG_REG_P1_HDRS_AFTER_BASIC :
			       NIG_REG_P0_HDRS_AFTER_BASIC,
			       IS_MF_SD(bp) ? 7 : 6);

		if (CHIP_IS_E3(bp))
			REG_WR(bp, BP_PORT(bp) ?
				   NIG_REG_LLH1_MF_MODE :
				   NIG_REG_LLH_MF_MODE, IS_MF(bp));
	}
	if (!CHIP_IS_E3(bp))
		REG_WR(bp, NIG_REG_XGXS_SERDES0_MODE_SEL + port*4, 1);

	if (!CHIP_IS_E1(bp)) {
		/* 0x2 disable mf_ov, 0x1 enable */
		REG_WR(bp, NIG_REG_LLH0_BRB1_DRV_MASK_MF + port*4,
		       (IS_MF_SD(bp) ? 0x1 : 0x2));

		if (!CHIP_IS_E1x(bp)) {
			val = 0;
			switch (bp->mf_mode) {
			case MULTI_FUNCTION_SD:
				val = 1;
				break;
			case MULTI_FUNCTION_SI:
			case MULTI_FUNCTION_AFEX:
				val = 2;
				break;
			}

			REG_WR(bp, (BP_PORT(bp) ? NIG_REG_LLH1_CLS_TYPE :
						  NIG_REG_LLH0_CLS_TYPE), val);
		}
		{
			REG_WR(bp, NIG_REG_LLFC_ENABLE_0 + port*4, 0);
			REG_WR(bp, NIG_REG_LLFC_OUT_EN_0 + port*4, 0);
			REG_WR(bp, NIG_REG_PAUSE_ENABLE_0 + port*4, 1);
		}
	}

	/* If SPIO5 is set to generate interrupts, enable it for this port */
	val = REG_RD(bp, MISC_REG_SPIO_EVENT_EN);
	if (val & MISC_SPIO_SPIO5) {
		u32 reg_addr = (port ? MISC_REG_AEU_ENABLE1_FUNC_1_OUT_0 :
				       MISC_REG_AEU_ENABLE1_FUNC_0_OUT_0);
		val = REG_RD(bp, reg_addr);
		val |= AEU_INPUTS_ATTN_BITS_SPIO5;
		REG_WR(bp, reg_addr, val);
	}

	return 0;
}