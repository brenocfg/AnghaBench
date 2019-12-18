#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int ACPI_ARRAY_LENGTH (TYPE_1__*) ; 
 int /*<<< orphan*/  ACPI_STRCMP (char*,char*) ; 
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_1__* acpi_interfaces_supported ; 

acpi_status acpi_osi_invalidate(char *interface)
{
	int i;

	for (i = 0; i < ACPI_ARRAY_LENGTH(acpi_interfaces_supported); i++) {
		if (!ACPI_STRCMP(interface, acpi_interfaces_supported[i].name)) {
			*acpi_interfaces_supported[i].name = '\0';
			return AE_OK;
		}
	}
	return AE_NOT_FOUND;
}