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
 unsigned int AU1000_INTC0_INT_BASE ; 
 int /*<<< orphan*/  IC0_FALLINGCLR ; 
 int /*<<< orphan*/  IC0_RISINGCLR ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void au1x_ic0_ack(unsigned int irq_nr)
{
	unsigned int bit = irq_nr - AU1000_INTC0_INT_BASE;

	/*
	 * This may assume that we don't get interrupts from
	 * both edges at once, or if we do, that we don't care.
	 */
	au_writel(1 << bit, IC0_FALLINGCLR);
	au_writel(1 << bit, IC0_RISINGCLR);
	au_sync();
}