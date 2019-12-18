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

/* Variables and functions */
 int /*<<< orphan*/  LPD270_INT_MASK ; 
 int /*<<< orphan*/  LPD270_INT_STATUS ; 
 unsigned int LPD270_IRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (int,int /*<<< orphan*/ ) ; 
 int lpd270_irq_enabled ; 

__attribute__((used)) static void lpd270_mask_irq(unsigned int irq)
{
	int lpd270_irq = irq - LPD270_IRQ(0);

	__raw_writew(~(1 << lpd270_irq), LPD270_INT_STATUS);

	lpd270_irq_enabled &= ~(1 << lpd270_irq);
	__raw_writew(lpd270_irq_enabled, LPD270_INT_MASK);
}