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
struct irq_desc {int dummy; } ;
typedef  int /*<<< orphan*/  GEDR ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_bit (int /*<<< orphan*/ ) ; 
 unsigned int PCM027_IRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCM990_CTRL_INT_IRQ_GPIO ; 
 unsigned long PCM990_INTSETCLR ; 
 unsigned int __ffs (unsigned long) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 scalar_t__ likely (unsigned long) ; 
 unsigned long pcm990_irq_enabled ; 

__attribute__((used)) static void pcm990_irq_handler(unsigned int irq, struct irq_desc *desc)
{
	unsigned long pending = (~PCM990_INTSETCLR) & pcm990_irq_enabled;

	do {
		GEDR(PCM990_CTRL_INT_IRQ_GPIO) =
					GPIO_bit(PCM990_CTRL_INT_IRQ_GPIO);
		if (likely(pending)) {
			irq = PCM027_IRQ(0) + __ffs(pending);
			generic_handle_irq(irq);
		}
		pending = (~PCM990_INTSETCLR) & pcm990_irq_enabled;
	} while (pending);
}