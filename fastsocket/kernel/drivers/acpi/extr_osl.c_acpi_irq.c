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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  acpi_irq_context ; 
 int /*<<< orphan*/  acpi_irq_handled ; 
 scalar_t__ acpi_irq_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_irq_not_handled ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t acpi_irq(int irq, void *dev_id)
{
	u32 handled;

	handled = (*acpi_irq_handler) (acpi_irq_context);

	if (handled) {
		acpi_irq_handled++;
		return IRQ_HANDLED;
	} else {
		acpi_irq_not_handled++;
		return IRQ_NONE;
	}
}