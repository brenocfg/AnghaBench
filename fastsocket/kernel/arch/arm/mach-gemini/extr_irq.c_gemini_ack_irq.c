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
 int /*<<< orphan*/  GEMINI_INTERRUPT_BASE ; 
 int /*<<< orphan*/  IO_ADDRESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gemini_ack_irq(unsigned int irq)
{
	__raw_writel(1 << irq, IRQ_CLEAR(IO_ADDRESS(GEMINI_INTERRUPT_BASE)));
}