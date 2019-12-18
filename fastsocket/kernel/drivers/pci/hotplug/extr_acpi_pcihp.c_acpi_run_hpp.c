#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_4__ {int count; union acpi_object* elements; } ;
union acpi_object {scalar_t__ type; TYPE_3__ integer; TYPE_1__ package; } ;
struct TYPE_5__ {int revision; int /*<<< orphan*/  enable_perr; int /*<<< orphan*/  enable_serr; int /*<<< orphan*/  latency_timer; int /*<<< orphan*/  cache_line_size; } ;
struct hotplug_params {TYPE_2__* t0; TYPE_2__ type0_data; } ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct hotplug_params*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static acpi_status
acpi_run_hpp(acpi_handle handle, struct hotplug_params *hpp)
{
	acpi_status status;
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object *package, *fields;
	int i;

	memset(hpp, 0, sizeof(struct hotplug_params));

	status = acpi_evaluate_object(handle, "_HPP", NULL, &buffer);
	if (ACPI_FAILURE(status))
		return status;

	package = (union acpi_object *) buffer.pointer;
	if (package->type != ACPI_TYPE_PACKAGE ||
	    package->package.count != 4) {
		status = AE_ERROR;
		goto exit;
	}

	fields = package->package.elements;
	for (i = 0; i < 4; i++) {
		if (fields[i].type != ACPI_TYPE_INTEGER) {
			status = AE_ERROR;
			goto exit;
		}
	}

	hpp->t0 = &hpp->type0_data;
	hpp->t0->revision        = 1;
	hpp->t0->cache_line_size = fields[0].integer.value;
	hpp->t0->latency_timer   = fields[1].integer.value;
	hpp->t0->enable_serr     = fields[2].integer.value;
	hpp->t0->enable_perr     = fields[3].integer.value;

exit:
	kfree(buffer.pointer);
	return status;
}