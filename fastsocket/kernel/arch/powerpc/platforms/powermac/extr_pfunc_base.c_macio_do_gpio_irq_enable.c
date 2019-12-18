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
struct pmf_function {TYPE_1__* node; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NO_IRQ ; 
 unsigned int irq_of_parse_and_map (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macio_gpio_irq ; 
 int request_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pmf_function*) ; 

__attribute__((used)) static int macio_do_gpio_irq_enable(struct pmf_function *func)
{
	unsigned int irq = irq_of_parse_and_map(func->node, 0);
	if (irq == NO_IRQ)
		return -EINVAL;
	return request_irq(irq, macio_gpio_irq, 0, func->node->name, func);
}