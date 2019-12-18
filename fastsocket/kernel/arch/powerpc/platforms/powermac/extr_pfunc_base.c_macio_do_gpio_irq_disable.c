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
struct pmf_function {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NO_IRQ ; 
 int /*<<< orphan*/  free_irq (unsigned int,struct pmf_function*) ; 
 unsigned int irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int macio_do_gpio_irq_disable(struct pmf_function *func)
{
	unsigned int irq = irq_of_parse_and_map(func->node, 0);
	if (irq == NO_IRQ)
		return -EINVAL;
	free_irq(irq, func);
	return 0;
}