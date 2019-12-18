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
 int EBUSY ; 
 int EINVAL ; 
 int acpi_debug_trace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  trace_debug_layer ; 
 int /*<<< orphan*/  trace_debug_level ; 
 char* trace_method_name ; 

__attribute__((used)) static int param_set_trace_state(const char *val, struct kernel_param *kp)
{
	int result = 0;

	if (!strncmp(val, "enable", strlen("enable") - 1)) {
		result = acpi_debug_trace(trace_method_name, trace_debug_level,
					  trace_debug_layer, 0);
		if (result)
			result = -EBUSY;
		goto exit;
	}

	if (!strncmp(val, "disable", strlen("disable") - 1)) {
		int name = 0;
		result = acpi_debug_trace((char *)&name, trace_debug_level,
					  trace_debug_layer, 0);
		if (result)
			result = -EBUSY;
		goto exit;
	}

	if (!strncmp(val, "1", 1)) {
		result = acpi_debug_trace(trace_method_name, trace_debug_level,
					  trace_debug_layer, 1);
		if (result)
			result = -EBUSY;
		goto exit;
	}

	result = -EINVAL;
exit:
	return result;
}