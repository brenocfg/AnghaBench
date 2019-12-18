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

/* Variables and functions */
 int /*<<< orphan*/  Devices_print_command ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

int Devices_SetPrintCommand(const char *command)
{
	const char *p = command;
	int was_percent_s = FALSE;
	while (*p != '\0') {
		if (*p++ == '%') {
			char c = *p++;
			if (c == '%')
				continue; /* %% is safe */
			if (c == 's' && !was_percent_s) {
				was_percent_s = TRUE; /* only one %s is safe */
				continue;
			}
			return FALSE;
		}
	}
	strcpy(Devices_print_command, command);
	return TRUE;
}