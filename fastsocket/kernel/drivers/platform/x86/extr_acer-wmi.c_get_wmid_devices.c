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
struct TYPE_2__ {int length; scalar_t__ pointer; } ;
union acpi_object {scalar_t__ type; TYPE_1__ buffer; } ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  WMID_GUID2 ; 
 int /*<<< orphan*/  wmi_query_block (int /*<<< orphan*/ ,int,struct acpi_buffer*) ; 

__attribute__((used)) static u32 get_wmid_devices(void)
{
	struct acpi_buffer out = {ACPI_ALLOCATE_BUFFER, NULL};
	union acpi_object *obj;
	acpi_status status;

	status = wmi_query_block(WMID_GUID2, 1, &out);
	if (ACPI_FAILURE(status))
		return 0;

	obj = (union acpi_object *) out.pointer;
	if (obj && obj->type == ACPI_TYPE_BUFFER &&
		obj->buffer.length == sizeof(u32)) {
		return *((u32 *) obj->buffer.pointer);
	} else {
		return 0;
	}
}