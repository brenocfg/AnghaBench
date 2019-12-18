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
struct irq_desc {int /*<<< orphan*/ * handle_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_bad_irq ; 

void compat_irq_chip_set_default_handler(struct irq_desc *desc)
{
	/*
	 * If the architecture still has not overriden
	 * the flow handler then zap the default. This
	 * should catch incorrect flow-type setting.
	 */
	if (desc->handle_irq == &handle_bad_irq)
		desc->handle_irq = NULL;
}