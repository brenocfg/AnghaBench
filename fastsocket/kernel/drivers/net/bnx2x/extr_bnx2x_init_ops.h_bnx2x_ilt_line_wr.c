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
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1 (struct bnx2x*) ; 
 int /*<<< orphan*/  ILT_ADDR1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILT_ADDR2 (int /*<<< orphan*/ ) ; 
 scalar_t__ PXP2_REG_RQ_ONCHIP_AT ; 
 scalar_t__ PXP2_REG_RQ_ONCHIP_AT_B0 ; 
 int /*<<< orphan*/  bnx2x_wr_64 (struct bnx2x*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_ilt_line_wr(struct bnx2x *bp, int abs_idx,
			      dma_addr_t page_mapping)
{
	u32 reg;

	if (CHIP_IS_E1(bp))
		reg = PXP2_REG_RQ_ONCHIP_AT + abs_idx*8;
	else
		reg = PXP2_REG_RQ_ONCHIP_AT_B0 + abs_idx*8;

	bnx2x_wr_64(bp, reg, ILT_ADDR1(page_mapping), ILT_ADDR2(page_mapping));
}