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
typedef  scalar_t__ u32 ;
struct dmae_command {int dst_addr_lo; int len; int comp_addr_lo; int comp_val; scalar_t__ comp_addr_hi; scalar_t__ dst_addr_hi; int /*<<< orphan*/  src_addr_hi; int /*<<< orphan*/  src_addr_lo; scalar_t__ opcode; } ;
struct bnx2x {scalar_t__ func_stx; scalar_t__ executer_idx; int /*<<< orphan*/  func_stats; struct dmae_command stats_dmae; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1 (struct bnx2x*) ; 
 scalar_t__ CHIP_REV_IS_SLOW (struct bnx2x*) ; 
 int /*<<< orphan*/  DMAE_COMP_GRC ; 
 scalar_t__ DMAE_COMP_VAL ; 
 int /*<<< orphan*/  DMAE_DST_GRC ; 
 int DMAE_REG_CMD_MEM ; 
 int /*<<< orphan*/  DMAE_SRC_PCI ; 
 int PMF_DMAE_C (struct bnx2x*) ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 scalar_t__ bnx2x_dmae_opcode (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ bnx2x_dmae_opcode_clr_src_reset (scalar_t__) ; 
 int /*<<< orphan*/  bnx2x_issue_dmae_with_comp (struct bnx2x*,struct dmae_command*,scalar_t__*) ; 
 int /*<<< orphan*/  bnx2x_post_dmae (struct bnx2x*,struct dmae_command*,int) ; 
 scalar_t__* bnx2x_sp (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_sp_mapping (struct bnx2x*,struct dmae_command) ; 
 int* dmae_reg_go_c ; 
 int /*<<< orphan*/  func_stats ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct dmae_command*,int /*<<< orphan*/ ,int) ; 
 scalar_t__* stats_comp ; 

__attribute__((used)) static void bnx2x_hw_stats_post(struct bnx2x *bp)
{
	struct dmae_command *dmae = &bp->stats_dmae;
	u32 *stats_comp = bnx2x_sp(bp, stats_comp);

	*stats_comp = DMAE_COMP_VAL;
	if (CHIP_REV_IS_SLOW(bp))
		return;

	/* Update MCP's statistics if possible */
	if (bp->func_stx)
		memcpy(bnx2x_sp(bp, func_stats), &bp->func_stats,
		       sizeof(bp->func_stats));

	/* loader */
	if (bp->executer_idx) {
		int loader_idx = PMF_DMAE_C(bp);
		u32 opcode =  bnx2x_dmae_opcode(bp, DMAE_SRC_PCI, DMAE_DST_GRC,
						 true, DMAE_COMP_GRC);
		opcode = bnx2x_dmae_opcode_clr_src_reset(opcode);

		memset(dmae, 0, sizeof(struct dmae_command));
		dmae->opcode = opcode;
		dmae->src_addr_lo = U64_LO(bnx2x_sp_mapping(bp, dmae[0]));
		dmae->src_addr_hi = U64_HI(bnx2x_sp_mapping(bp, dmae[0]));
		dmae->dst_addr_lo = (DMAE_REG_CMD_MEM +
				     sizeof(struct dmae_command) *
				     (loader_idx + 1)) >> 2;
		dmae->dst_addr_hi = 0;
		dmae->len = sizeof(struct dmae_command) >> 2;
		if (CHIP_IS_E1(bp))
			dmae->len--;
		dmae->comp_addr_lo = dmae_reg_go_c[loader_idx + 1] >> 2;
		dmae->comp_addr_hi = 0;
		dmae->comp_val = 1;

		*stats_comp = 0;
		bnx2x_post_dmae(bp, dmae, loader_idx);

	} else if (bp->func_stx) {
		*stats_comp = 0;
		bnx2x_issue_dmae_with_comp(bp, dmae, stats_comp);
	}
}