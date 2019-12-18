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
 int /*<<< orphan*/  VIPER_CPLD_GPIO ; 
 int /*<<< orphan*/  __ffs (unsigned long) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 scalar_t__ likely (unsigned long) ; 
 unsigned int viper_bit_to_irq (int /*<<< orphan*/ ) ; 
 unsigned long viper_irq_pending () ; 

__attribute__((used)) static void viper_irq_handler(unsigned int irq, struct irq_desc *desc)
{
	unsigned long pending;

	pending = viper_irq_pending();
	do {
		/* we're in a chained irq handler,
		 * so ack the interrupt by hand */
		GEDR(VIPER_CPLD_GPIO) = GPIO_bit(VIPER_CPLD_GPIO);

		if (likely(pending)) {
			irq = viper_bit_to_irq(__ffs(pending));
			generic_handle_irq(irq);
		}
		pending = viper_irq_pending();
	} while (pending);
}