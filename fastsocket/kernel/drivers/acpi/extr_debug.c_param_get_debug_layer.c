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
struct kernel_param {int dummy; } ;
struct TYPE_3__ {char* name; int value; } ;

/* Variables and functions */
 int ACPI_ALL_DRIVERS ; 
 int ARRAY_SIZE (TYPE_1__*) ; 
 int acpi_dbg_layer ; 
 TYPE_1__* acpi_debug_layers ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static int param_get_debug_layer(char *buffer, struct kernel_param *kp) {
	int result = 0;
	int i;

	result = sprintf(buffer, "%-25s\tHex        SET\n", "Description");

	for(i = 0; i <ARRAY_SIZE(acpi_debug_layers); i++) {
		result += sprintf(buffer+result, "%-25s\t0x%08lX [%c]\n",
					acpi_debug_layers[i].name,
					acpi_debug_layers[i].value,
					(acpi_dbg_layer & acpi_debug_layers[i].value) ? '*' : ' ');
	}
	result += sprintf(buffer+result, "%-25s\t0x%08X [%c]\n", "ACPI_ALL_DRIVERS",
					ACPI_ALL_DRIVERS,
					(acpi_dbg_layer & ACPI_ALL_DRIVERS) ==
					ACPI_ALL_DRIVERS ? '*' : (acpi_dbg_layer &
					ACPI_ALL_DRIVERS) == 0 ? ' ' : '-');
	result += sprintf(buffer+result, "--\ndebug_layer = 0x%08X ( * = enabled)\n", acpi_dbg_layer);

	return result;
}