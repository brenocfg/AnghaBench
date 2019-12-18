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
typedef  unsigned int u32 ;

/* Variables and functions */
 scalar_t__ GT641XX_IRQ_BASE ; 
 int /*<<< orphan*/  GT_INTRCAUSE_OFS ; 
 int /*<<< orphan*/  GT_INTRMASK_OFS ; 
 unsigned int GT_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_IRQ (scalar_t__) ; 
 int /*<<< orphan*/  irq_err_count ; 

void gt641xx_irq_dispatch(void)
{
	u32 cause, mask;
	int i;

	cause = GT_READ(GT_INTRCAUSE_OFS);
	mask = GT_READ(GT_INTRMASK_OFS);
	cause &= mask;

	/*
	 * bit0 : logical or of all the interrupt bits.
	 * bit30: logical or of bits[29:26,20:1].
	 * bit31: logical or of bits[25:1].
	 */
	for (i = 1; i < 30; i++) {
		if (cause & (1U << i)) {
			do_IRQ(GT641XX_IRQ_BASE + i);
			return;
		}
	}

	atomic_inc(&irq_err_count);
}