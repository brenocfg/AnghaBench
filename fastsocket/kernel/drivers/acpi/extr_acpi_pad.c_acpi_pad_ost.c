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
struct TYPE_3__ {int length; void* pointer; } ;
struct TYPE_4__ {int value; } ;
union acpi_object {TYPE_1__ buffer; TYPE_2__ integer; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  uint32_t ;
struct acpi_object_list {int member_0; union acpi_object* member_1; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int ACPI_PROCESSOR_AGGREGATOR_NOTIFY ; 
 int /*<<< orphan*/  ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,struct acpi_object_list*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_pad_ost(acpi_handle handle, int stat,
	uint32_t idle_cpus)
{
	union acpi_object params[3] = {
		{.type = ACPI_TYPE_INTEGER,},
		{.type = ACPI_TYPE_INTEGER,},
		{.type = ACPI_TYPE_BUFFER,},
	};
	struct acpi_object_list arg_list = {3, params};

	params[0].integer.value = ACPI_PROCESSOR_AGGREGATOR_NOTIFY;
	params[1].integer.value =  stat;
	params[2].buffer.length = 4;
	params[2].buffer.pointer = (void *)&idle_cpus;
	acpi_evaluate_object(handle, "_OST", &arg_list, NULL);
}