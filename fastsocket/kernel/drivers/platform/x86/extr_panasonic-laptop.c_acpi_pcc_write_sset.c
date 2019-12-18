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
struct TYPE_2__ {int value; int /*<<< orphan*/  type; } ;
union acpi_object {TYPE_1__ integer; } ;
struct pcc_acpi {int /*<<< orphan*/  handle; } ;
struct acpi_object_list {union acpi_object* pointer; int /*<<< orphan*/  count; } ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 scalar_t__ AE_OK ; 
 int /*<<< orphan*/  ARRAY_SIZE (union acpi_object*) ; 
 int /*<<< orphan*/  METHOD_HKEY_SSET ; 
 scalar_t__ acpi_evaluate_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_object_list*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_pcc_write_sset(struct pcc_acpi *pcc, int func, int val)
{
	union acpi_object in_objs[] = {
		{ .integer.type  = ACPI_TYPE_INTEGER,
		  .integer.value = func, },
		{ .integer.type  = ACPI_TYPE_INTEGER,
		  .integer.value = val, },
	};
	struct acpi_object_list params = {
		.count   = ARRAY_SIZE(in_objs),
		.pointer = in_objs,
	};
	acpi_status status = AE_OK;

	status = acpi_evaluate_object(pcc->handle, METHOD_HKEY_SSET,
				      &params, NULL);

	return status == AE_OK;
}