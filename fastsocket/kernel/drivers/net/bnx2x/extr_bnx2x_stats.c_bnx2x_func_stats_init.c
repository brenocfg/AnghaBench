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
struct host_func_stats {int dummy; } ;
struct dmae_command {int dst_addr_lo; int len; int /*<<< orphan*/  comp_val; void* comp_addr_hi; void* comp_addr_lo; scalar_t__ dst_addr_hi; void* src_addr_hi; void* src_addr_lo; int /*<<< orphan*/  opcode; } ;
struct bnx2x {int func_stx; scalar_t__ executer_idx; struct dmae_command stats_dmae; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  DMAE_COMP_PCI ; 
 int /*<<< orphan*/  DMAE_COMP_VAL ; 
 int /*<<< orphan*/  DMAE_DST_GRC ; 
 int /*<<< orphan*/  DMAE_SRC_PCI ; 
 void* U64_HI (int /*<<< orphan*/ ) ; 
 void* U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_dmae_opcode (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__* bnx2x_sp (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_sp_mapping (struct bnx2x*,scalar_t__*) ; 
 scalar_t__* func_stats ; 
 int /*<<< orphan*/  memset (struct dmae_command*,int /*<<< orphan*/ ,int) ; 
 scalar_t__* stats_comp ; 

__attribute__((used)) static void bnx2x_func_stats_init(struct bnx2x *bp)
{
	struct dmae_command *dmae = &bp->stats_dmae;
	u32 *stats_comp = bnx2x_sp(bp, stats_comp);

	/* sanity */
	if (!bp->func_stx) {
		BNX2X_ERR("BUG!\n");
		return;
	}

	bp->executer_idx = 0;
	memset(dmae, 0, sizeof(struct dmae_command));

	dmae->opcode = bnx2x_dmae_opcode(bp, DMAE_SRC_PCI, DMAE_DST_GRC,
					 true, DMAE_COMP_PCI);
	dmae->src_addr_lo = U64_LO(bnx2x_sp_mapping(bp, func_stats));
	dmae->src_addr_hi = U64_HI(bnx2x_sp_mapping(bp, func_stats));
	dmae->dst_addr_lo = bp->func_stx >> 2;
	dmae->dst_addr_hi = 0;
	dmae->len = sizeof(struct host_func_stats) >> 2;
	dmae->comp_addr_lo = U64_LO(bnx2x_sp_mapping(bp, stats_comp));
	dmae->comp_addr_hi = U64_HI(bnx2x_sp_mapping(bp, stats_comp));
	dmae->comp_val = DMAE_COMP_VAL;

	*stats_comp = 0;
}