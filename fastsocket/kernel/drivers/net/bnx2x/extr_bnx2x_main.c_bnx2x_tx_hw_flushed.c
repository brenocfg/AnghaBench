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
typedef  int /*<<< orphan*/  u32 ;
struct pbf_pN_cmd_regs {int member_0; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct pbf_pN_buf_regs {int member_0; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct pbf_pN_cmd_regs*) ; 
 int /*<<< orphan*/  CHIP_IS_E3B0 (struct bnx2x*) ; 
 int /*<<< orphan*/  PBF_REG_CREDIT_LB_Q ; 
 int /*<<< orphan*/  PBF_REG_CREDIT_Q0 ; 
 int /*<<< orphan*/  PBF_REG_CREDIT_Q1 ; 
 int /*<<< orphan*/  PBF_REG_INIT_CRD_LB_Q ; 
 int /*<<< orphan*/  PBF_REG_INIT_CRD_Q0 ; 
 int /*<<< orphan*/  PBF_REG_INIT_CRD_Q1 ; 
 int /*<<< orphan*/  PBF_REG_INTERNAL_CRD_FREED_CNT_LB_Q ; 
 int /*<<< orphan*/  PBF_REG_INTERNAL_CRD_FREED_CNT_Q0 ; 
 int /*<<< orphan*/  PBF_REG_INTERNAL_CRD_FREED_CNT_Q1 ; 
 int /*<<< orphan*/  PBF_REG_P0_CREDIT ; 
 int /*<<< orphan*/  PBF_REG_P0_INIT_CRD ; 
 int /*<<< orphan*/  PBF_REG_P0_INTERNAL_CRD_FREED_CNT ; 
 int /*<<< orphan*/  PBF_REG_P0_TQ_LINES_FREED_CNT ; 
 int /*<<< orphan*/  PBF_REG_P0_TQ_OCCUPANCY ; 
 int /*<<< orphan*/  PBF_REG_P1_CREDIT ; 
 int /*<<< orphan*/  PBF_REG_P1_INIT_CRD ; 
 int /*<<< orphan*/  PBF_REG_P1_INTERNAL_CRD_FREED_CNT ; 
 int /*<<< orphan*/  PBF_REG_P1_TQ_LINES_FREED_CNT ; 
 int /*<<< orphan*/  PBF_REG_P1_TQ_OCCUPANCY ; 
 int /*<<< orphan*/  PBF_REG_P4_CREDIT ; 
 int /*<<< orphan*/  PBF_REG_P4_INIT_CRD ; 
 int /*<<< orphan*/  PBF_REG_P4_INTERNAL_CRD_FREED_CNT ; 
 int /*<<< orphan*/  PBF_REG_P4_TQ_LINES_FREED_CNT ; 
 int /*<<< orphan*/  PBF_REG_P4_TQ_OCCUPANCY ; 
 int /*<<< orphan*/  PBF_REG_TQ_LINES_FREED_CNT_LB_Q ; 
 int /*<<< orphan*/  PBF_REG_TQ_LINES_FREED_CNT_Q0 ; 
 int /*<<< orphan*/  PBF_REG_TQ_LINES_FREED_CNT_Q1 ; 
 int /*<<< orphan*/  PBF_REG_TQ_OCCUPANCY_LB_Q ; 
 int /*<<< orphan*/  PBF_REG_TQ_OCCUPANCY_Q0 ; 
 int /*<<< orphan*/  PBF_REG_TQ_OCCUPANCY_Q1 ; 
 int /*<<< orphan*/  bnx2x_pbf_pN_buf_flushed (struct bnx2x*,struct pbf_pN_cmd_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_pbf_pN_cmd_flushed (struct bnx2x*,struct pbf_pN_cmd_regs*,int /*<<< orphan*/ ) ; 

void bnx2x_tx_hw_flushed(struct bnx2x *bp, u32 poll_count)
{
	struct pbf_pN_cmd_regs cmd_regs[] = {
		{0, (CHIP_IS_E3B0(bp)) ?
			PBF_REG_TQ_OCCUPANCY_Q0 :
			PBF_REG_P0_TQ_OCCUPANCY,
		    (CHIP_IS_E3B0(bp)) ?
			PBF_REG_TQ_LINES_FREED_CNT_Q0 :
			PBF_REG_P0_TQ_LINES_FREED_CNT},
		{1, (CHIP_IS_E3B0(bp)) ?
			PBF_REG_TQ_OCCUPANCY_Q1 :
			PBF_REG_P1_TQ_OCCUPANCY,
		    (CHIP_IS_E3B0(bp)) ?
			PBF_REG_TQ_LINES_FREED_CNT_Q1 :
			PBF_REG_P1_TQ_LINES_FREED_CNT},
		{4, (CHIP_IS_E3B0(bp)) ?
			PBF_REG_TQ_OCCUPANCY_LB_Q :
			PBF_REG_P4_TQ_OCCUPANCY,
		    (CHIP_IS_E3B0(bp)) ?
			PBF_REG_TQ_LINES_FREED_CNT_LB_Q :
			PBF_REG_P4_TQ_LINES_FREED_CNT}
	};

	struct pbf_pN_buf_regs buf_regs[] = {
		{0, (CHIP_IS_E3B0(bp)) ?
			PBF_REG_INIT_CRD_Q0 :
			PBF_REG_P0_INIT_CRD ,
		    (CHIP_IS_E3B0(bp)) ?
			PBF_REG_CREDIT_Q0 :
			PBF_REG_P0_CREDIT,
		    (CHIP_IS_E3B0(bp)) ?
			PBF_REG_INTERNAL_CRD_FREED_CNT_Q0 :
			PBF_REG_P0_INTERNAL_CRD_FREED_CNT},
		{1, (CHIP_IS_E3B0(bp)) ?
			PBF_REG_INIT_CRD_Q1 :
			PBF_REG_P1_INIT_CRD,
		    (CHIP_IS_E3B0(bp)) ?
			PBF_REG_CREDIT_Q1 :
			PBF_REG_P1_CREDIT,
		    (CHIP_IS_E3B0(bp)) ?
			PBF_REG_INTERNAL_CRD_FREED_CNT_Q1 :
			PBF_REG_P1_INTERNAL_CRD_FREED_CNT},
		{4, (CHIP_IS_E3B0(bp)) ?
			PBF_REG_INIT_CRD_LB_Q :
			PBF_REG_P4_INIT_CRD,
		    (CHIP_IS_E3B0(bp)) ?
			PBF_REG_CREDIT_LB_Q :
			PBF_REG_P4_CREDIT,
		    (CHIP_IS_E3B0(bp)) ?
			PBF_REG_INTERNAL_CRD_FREED_CNT_LB_Q :
			PBF_REG_P4_INTERNAL_CRD_FREED_CNT},
	};

	int i;

	/* Verify the command queues are flushed P0, P1, P4 */
	for (i = 0; i < ARRAY_SIZE(cmd_regs); i++)
		bnx2x_pbf_pN_cmd_flushed(bp, &cmd_regs[i], poll_count);

	/* Verify the transmission buffers are flushed P0, P1, P4 */
	for (i = 0; i < ARRAY_SIZE(buf_regs); i++)
		bnx2x_pbf_pN_buf_flushed(bp, &buf_regs[i], poll_count);
}