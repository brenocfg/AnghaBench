#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct acpi_processor {TYPE_2__* pdc; } ;
struct TYPE_3__ {TYPE_2__* pointer; } ;
struct TYPE_4__ {struct TYPE_4__* pointer; TYPE_1__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 

void arch_acpi_processor_cleanup_pdc(struct acpi_processor *pr)
{
	if (pr->pdc) {
		kfree(pr->pdc->pointer->buffer.pointer);
		kfree(pr->pdc->pointer);
		kfree(pr->pdc);
		pr->pdc = NULL;
	}
}