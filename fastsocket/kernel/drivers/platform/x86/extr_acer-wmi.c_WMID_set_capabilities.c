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
struct TYPE_3__ {int length; scalar_t__ pointer; } ;
union acpi_object {scalar_t__ type; TYPE_1__ buffer; } ;
typedef  int u32 ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_4__ {int /*<<< orphan*/  capability; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACER_CAP_BLUETOOTH ; 
 int /*<<< orphan*/  ACER_CAP_BRIGHTNESS ; 
 int /*<<< orphan*/  ACER_CAP_THREEG ; 
 int /*<<< orphan*/  ACER_CAP_WIRELESS ; 
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  WMID_GUID2 ; 
 TYPE_2__* interface ; 
 int max_brightness ; 
 int /*<<< orphan*/  wmi_query_block (int /*<<< orphan*/ ,int,struct acpi_buffer*) ; 

__attribute__((used)) static acpi_status WMID_set_capabilities(void)
{
	struct acpi_buffer out = {ACPI_ALLOCATE_BUFFER, NULL};
	union acpi_object *obj;
	acpi_status status;
	u32 devices;

	status = wmi_query_block(WMID_GUID2, 1, &out);
	if (ACPI_FAILURE(status))
		return status;

	obj = (union acpi_object *) out.pointer;
	if (obj && obj->type == ACPI_TYPE_BUFFER &&
		obj->buffer.length == sizeof(u32)) {
		devices = *((u32 *) obj->buffer.pointer);
	} else {
		return AE_ERROR;
	}

	/* Not sure on the meaning of the relevant bits yet to detect these */
	interface->capability |= ACER_CAP_WIRELESS;
	interface->capability |= ACER_CAP_THREEG;

	/* WMID always provides brightness methods */
	interface->capability |= ACER_CAP_BRIGHTNESS;

	if (devices & 0x10)
		interface->capability |= ACER_CAP_BLUETOOTH;

	if (!(devices & 0x20))
		max_brightness = 0x9;

	return status;
}