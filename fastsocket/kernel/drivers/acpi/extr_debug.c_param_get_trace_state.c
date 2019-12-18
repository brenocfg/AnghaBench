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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int acpi_gbl_trace_flags ; 
 int /*<<< orphan*/  acpi_gbl_trace_method_name ; 
 int sprintf (char*,char*) ; 

__attribute__((used)) static int param_get_trace_state(char *buffer, struct kernel_param *kp)
{
	if (!acpi_gbl_trace_method_name)
		return sprintf(buffer, "disable");
	else {
		if (acpi_gbl_trace_flags & 1)
			return sprintf(buffer, "1");
		else
			return sprintf(buffer, "enable");
	}
	return 0;
}