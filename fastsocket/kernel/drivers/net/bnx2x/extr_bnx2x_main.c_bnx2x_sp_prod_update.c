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
struct bnx2x {int /*<<< orphan*/  spq_prod_idx; } ;

/* Variables and functions */
 scalar_t__ BAR_XSTRORM_INTMEM ; 
 int BP_FUNC (struct bnx2x*) ; 
 int /*<<< orphan*/  REG_WR16 (struct bnx2x*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ XSTORM_SPQ_PROD_OFFSET (int) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  mmiowb () ; 

__attribute__((used)) static void bnx2x_sp_prod_update(struct bnx2x *bp)
{
	int func = BP_FUNC(bp);

	/*
	 * Make sure that BD data is updated before writing the producer:
	 * BD data is written to the memory, the producer is read from the
	 * memory, thus we need a full memory barrier to ensure the ordering.
	 */
	mb();

	REG_WR16(bp, BAR_XSTRORM_INTMEM + XSTORM_SPQ_PROD_OFFSET(func),
		 bp->spq_prod_idx);
	mmiowb();
}