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
struct TYPE_2__ {int value; } ;
union acpi_object {scalar_t__ type; TYPE_1__ integer; } ;
typedef  int u8 ;
typedef  int u32 ;
struct acpi_buffer {scalar_t__ length; scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  GUID ; 
#define  TC1100_INSTANCE_JOGDIAL 129 
#define  TC1100_INSTANCE_WIRELESS 128 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  wmi_query_block (int /*<<< orphan*/ ,int,struct acpi_buffer*) ; 

__attribute__((used)) static int get_state(u32 *out, u8 instance)
{
	u32 tmp;
	acpi_status status;
	struct acpi_buffer result = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object *obj;

	if (!out)
		return -EINVAL;

	if (instance > 2)
		return -ENODEV;

	status = wmi_query_block(GUID, instance, &result);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	obj = (union acpi_object *) result.pointer;
	if (obj && obj->type == ACPI_TYPE_INTEGER) {
		tmp = obj->integer.value;
	} else {
		tmp = 0;
	}

	if (result.length > 0 && result.pointer)
		kfree(result.pointer);

	switch (instance) {
	case TC1100_INSTANCE_WIRELESS:
		*out = (tmp == 3) ? 1 : 0;
		return 0;
	case TC1100_INSTANCE_JOGDIAL:
		*out = (tmp == 1) ? 0 : 1;
		return 0;
	default:
		return -ENODEV;
	}
}