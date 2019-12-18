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
struct acpi_processor {int /*<<< orphan*/ * pdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_intel_pdc (struct acpi_processor*) ; 

void arch_acpi_processor_init_pdc(struct acpi_processor *pr)
{
	pr->pdc = NULL;
	init_intel_pdc(pr);
	return;
}