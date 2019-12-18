#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_8__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
struct event_ring_data {int /*<<< orphan*/  sb_id; int /*<<< orphan*/  index_id; int /*<<< orphan*/  producer; TYPE_4__ base_addr; TYPE_1__ member_0; } ;
struct cmng_struct_per_port {int dummy; } ;
struct bnx2x_func_init_params {int func_flgs; int pf_id; int func_id; int /*<<< orphan*/  spq_prod; int /*<<< orphan*/  spq_map; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {scalar_t__ pmf; } ;
struct TYPE_6__ {int /*<<< orphan*/  line_speed; } ;
struct bnx2x {int flags; int /*<<< orphan*/  eq_prod; int /*<<< orphan*/  eq_mapping; int /*<<< orphan*/  cmng; TYPE_3__ port; TYPE_2__ link_vars; int /*<<< orphan*/  spq_prod_idx; int /*<<< orphan*/  spq_mapping; } ;

/* Variables and functions */
 int BNX2X_IGU_STAS_MSG_PF_CNT ; 
 int BNX2X_IGU_STAS_MSG_VF_CNT ; 
 int BP_FUNC (struct bnx2x*) ; 
 int /*<<< orphan*/  BP_PORT (struct bnx2x*) ; 
 int BP_VN (struct bnx2x*) ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bnx2x*) ; 
 scalar_t__ CHIP_MODE_IS_4_PORT (struct bnx2x*) ; 
 int /*<<< orphan*/  DEF_SB_ID ; 
 int FUNC_FLG_LEADING ; 
 int FUNC_FLG_SPQ ; 
 int FUNC_FLG_STATS ; 
 int FUNC_FLG_TPA ; 
 int /*<<< orphan*/  HC_SP_INDEX_EQ_CONS ; 
 scalar_t__ IGU_REG_STATISTIC_NUM_MESSAGE_SENT ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int TPA_ENABLE_FLAG ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_cmng_fns_init (struct bnx2x*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_func_init (struct bnx2x*,struct bnx2x_func_init_params*) ; 
 int /*<<< orphan*/  bnx2x_get_cmng_fns_mode (struct bnx2x*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  storm_memset_cmng (struct bnx2x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storm_memset_eq_data (struct bnx2x*,struct event_ring_data*,int) ; 

__attribute__((used)) static void bnx2x_pf_init(struct bnx2x *bp)
{
	struct bnx2x_func_init_params func_init = {0};
	struct event_ring_data eq_data = { {0} };
	u16 flags;

	if (!CHIP_IS_E1x(bp)) {
		/* reset IGU PF statistics: MSIX + ATTN */
		/* PF */
		REG_WR(bp, IGU_REG_STATISTIC_NUM_MESSAGE_SENT +
			   BNX2X_IGU_STAS_MSG_VF_CNT*4 +
			   (CHIP_MODE_IS_4_PORT(bp) ?
				BP_FUNC(bp) : BP_VN(bp))*4, 0);
		/* ATTN */
		REG_WR(bp, IGU_REG_STATISTIC_NUM_MESSAGE_SENT +
			   BNX2X_IGU_STAS_MSG_VF_CNT*4 +
			   BNX2X_IGU_STAS_MSG_PF_CNT*4 +
			   (CHIP_MODE_IS_4_PORT(bp) ?
				BP_FUNC(bp) : BP_VN(bp))*4, 0);
	}

	/* function setup flags */
	flags = (FUNC_FLG_STATS | FUNC_FLG_LEADING | FUNC_FLG_SPQ);

	/* This flag is relevant for E1x only.
	 * E2 doesn't have a TPA configuration in a function level.
	 */
	flags |= (bp->flags & TPA_ENABLE_FLAG) ? FUNC_FLG_TPA : 0;

	func_init.func_flgs = flags;
	func_init.pf_id = BP_FUNC(bp);
	func_init.func_id = BP_FUNC(bp);
	func_init.spq_map = bp->spq_mapping;
	func_init.spq_prod = bp->spq_prod_idx;

	bnx2x_func_init(bp, &func_init);

	memset(&(bp->cmng), 0, sizeof(struct cmng_struct_per_port));

	/*
	 * Congestion management values depend on the link rate
	 * There is no active link so initial link rate is set to 10 Gbps.
	 * When the link comes up The congestion management values are
	 * re-calculated according to the actual link rate.
	 */
	bp->link_vars.line_speed = SPEED_10000;
	bnx2x_cmng_fns_init(bp, true, bnx2x_get_cmng_fns_mode(bp));

	/* Only the PMF sets the HW */
	if (bp->port.pmf)
		storm_memset_cmng(bp, &bp->cmng, BP_PORT(bp));

	/* init Event Queue - PCI bus guarantees correct endianity*/
	eq_data.base_addr.hi = U64_HI(bp->eq_mapping);
	eq_data.base_addr.lo = U64_LO(bp->eq_mapping);
	eq_data.producer = bp->eq_prod;
	eq_data.index_id = HC_SP_INDEX_EQ_CONS;
	eq_data.sb_id = DEF_SB_ID;
	storm_memset_eq_data(bp, &eq_data, BP_FUNC(bp));
}