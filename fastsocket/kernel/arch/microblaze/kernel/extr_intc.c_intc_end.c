#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int status; } ;

/* Variables and functions */
 scalar_t__ IAR ; 
 scalar_t__ INTC_BASE ; 
 int IRQ_DISABLED ; 
 int IRQ_INPROGRESS ; 
 int IRQ_LEVEL ; 
 scalar_t__ SIE ; 
 TYPE_1__* irq_desc ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 

__attribute__((used)) static void intc_end(unsigned int irq)
{
	unsigned long mask = 1 << irq;
	pr_debug("end: %d\n", irq);
	if (!(irq_desc[irq].status & (IRQ_DISABLED | IRQ_INPROGRESS))) {
		out_be32(INTC_BASE + SIE, mask);
		/* ack level sensitive intr */
		if (irq_desc[irq].status & IRQ_LEVEL)
			out_be32(INTC_BASE + IAR, mask);
	}
}