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
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  imask_irq_chip ; 
 int /*<<< orphan*/  set_irq_chip_and_handler_name (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void make_imask_irq(unsigned int irq)
{
	set_irq_chip_and_handler_name(irq, &imask_irq_chip,
				      handle_level_irq, "level");
}