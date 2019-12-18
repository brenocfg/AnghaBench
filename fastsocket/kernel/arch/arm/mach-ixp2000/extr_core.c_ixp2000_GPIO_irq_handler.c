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

/* Variables and functions */
 scalar_t__ IRQ_IXP2000_GPIO0 ; 
 unsigned long* IXP2000_GPIO_INST ; 
 int /*<<< orphan*/  generic_handle_irq (scalar_t__) ; 

__attribute__((used)) static void ixp2000_GPIO_irq_handler(unsigned int irq, struct irq_desc *desc)
{                               
	int i;
	unsigned long status = *IXP2000_GPIO_INST;
		   
	for (i = 0; i <= 7; i++) {
		if (status & (1<<i)) {
			generic_handle_irq(i + IRQ_IXP2000_GPIO0);
		}
	}
}