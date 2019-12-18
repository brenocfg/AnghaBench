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
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int acpi_object_type ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int ACPI_BUS_TYPE_DEVICE ; 
 int ACPI_BUS_TYPE_POWER ; 
 int ACPI_BUS_TYPE_PROCESSOR ; 
 int ACPI_BUS_TYPE_THERMAL ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 unsigned long long ACPI_STA_DEFAULT ; 
#define  ACPI_TYPE_ANY 132 
#define  ACPI_TYPE_DEVICE 131 
#define  ACPI_TYPE_POWER 130 
#define  ACPI_TYPE_PROCESSOR 129 
#define  ACPI_TYPE_THERMAL 128 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_bus_get_status_handle (int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_get_type (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int acpi_bus_type_and_status(acpi_handle handle, int *type,
				    unsigned long long *sta)
{
	acpi_status status;
	acpi_object_type acpi_type;

	status = acpi_get_type(handle, &acpi_type);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	switch (acpi_type) {
	case ACPI_TYPE_ANY:		/* for ACPI_ROOT_OBJECT */
	case ACPI_TYPE_DEVICE:
		*type = ACPI_BUS_TYPE_DEVICE;
		status = acpi_bus_get_status_handle(handle, sta);
		if (ACPI_FAILURE(status))
			return -ENODEV;
		break;
	case ACPI_TYPE_PROCESSOR:
		*type = ACPI_BUS_TYPE_PROCESSOR;
		status = acpi_bus_get_status_handle(handle, sta);
		if (ACPI_FAILURE(status))
			return -ENODEV;
		break;
	case ACPI_TYPE_THERMAL:
		*type = ACPI_BUS_TYPE_THERMAL;
		*sta = ACPI_STA_DEFAULT;
		break;
	case ACPI_TYPE_POWER:
		*type = ACPI_BUS_TYPE_POWER;
		*sta = ACPI_STA_DEFAULT;
		break;
	default:
		return -ENODEV;
	}

	return 0;
}