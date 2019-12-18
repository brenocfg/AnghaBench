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
typedef  int u8 ;
typedef  int u32 ;
struct acpi_buffer {int length; int* pointer; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  GUID ; 
#define  TC1100_INSTANCE_JOGDIAL 129 
#define  TC1100_INSTANCE_WIRELESS 128 
 int /*<<< orphan*/  wmi_set_block (int /*<<< orphan*/ ,int,struct acpi_buffer*) ; 

__attribute__((used)) static int set_state(u32 *in, u8 instance)
{
	u32 value;
	acpi_status status;
	struct acpi_buffer input;

	if (!in)
		return -EINVAL;

	if (instance > 2)
		return -ENODEV;

	switch (instance) {
	case TC1100_INSTANCE_WIRELESS:
		value = (*in) ? 1 : 2;
		break;
	case TC1100_INSTANCE_JOGDIAL:
		value = (*in) ? 0 : 1;
		break;
	default:
		return -ENODEV;
	}

	input.length = sizeof(u32);
	input.pointer = &value;

	status = wmi_set_block(GUID, instance, &input);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	return 0;
}