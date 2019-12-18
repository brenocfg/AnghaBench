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
typedef  int u32 ;
struct irq_desc {int /*<<< orphan*/  (* handle ) (unsigned int,struct irq_desc*) ;} ;

/* Variables and functions */
 int CPLD_LATCHED_INTS ; 
 unsigned int IRQ_KEV_7A400_CPLD ; 
 int /*<<< orphan*/  stub1 (unsigned int,struct irq_desc*) ; 

__attribute__((used)) static void
lh7a400_cpld_handler (unsigned int irq, struct irq_desc *desc)
{
	u32 mask = CPLD_LATCHED_INTS;
	irq = IRQ_KEV_7A400_CPLD;
	for (; mask; mask >>= 1, ++irq) {
		if (mask & 1)
			desc[irq].handle (irq, desc);
	}
}