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
struct TYPE_2__ {scalar_t__ pointer; } ;
union acpi_object {TYPE_1__ buffer; } ;
typedef  int u32 ;
struct acpi_processor {int /*<<< orphan*/  handle; struct acpi_object_list* pdc; } ;
struct acpi_object_list {union acpi_object* pointer; } ;
typedef  int acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int) ; 
 int ACPI_PDC_C_C1_FFH ; 
 int ACPI_PDC_C_C2C3_FFH ; 
 int AE_OK ; 
 int acpi_evaluate_object (int /*<<< orphan*/ ,char*,struct acpi_object_list*,int /*<<< orphan*/ *) ; 
 scalar_t__ idle_nomwait ; 

__attribute__((used)) static int acpi_processor_set_pdc(struct acpi_processor *pr)
{
	struct acpi_object_list *pdc_in = pr->pdc;
	acpi_status status = AE_OK;


	if (!pdc_in)
		return status;
	if (idle_nomwait) {
		/*
		 * If mwait is disabled for CPU C-states, the C2C3_FFH access
		 * mode will be disabled in the parameter of _PDC object.
		 * Of course C1_FFH access mode will also be disabled.
		 */
		union acpi_object *obj;
		u32 *buffer = NULL;

		obj = pdc_in->pointer;
		buffer = (u32 *)(obj->buffer.pointer);
		buffer[2] &= ~(ACPI_PDC_C_C2C3_FFH | ACPI_PDC_C_C1_FFH);

	}
	status = acpi_evaluate_object(pr->handle, "_PDC", pdc_in, NULL);

	if (ACPI_FAILURE(status))
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
		    "Could not evaluate _PDC, using legacy perf. control...\n"));

	return status;
}