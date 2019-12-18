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
typedef  size_t u8 ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_IS_PRINT (char) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,...) ; 

void acpi_ut_print_string(char *string, u8 max_length)
{
	u32 i;

	if (!string) {
		acpi_os_printf("<\"NULL STRING PTR\">");
		return;
	}

	acpi_os_printf("\"");
	for (i = 0; string[i] && (i < max_length); i++) {

		/* Escape sequences */

		switch (string[i]) {
		case 0x07:
			acpi_os_printf("\\a");	/* BELL */
			break;

		case 0x08:
			acpi_os_printf("\\b");	/* BACKSPACE */
			break;

		case 0x0C:
			acpi_os_printf("\\f");	/* FORMFEED */
			break;

		case 0x0A:
			acpi_os_printf("\\n");	/* LINEFEED */
			break;

		case 0x0D:
			acpi_os_printf("\\r");	/* CARRIAGE RETURN */
			break;

		case 0x09:
			acpi_os_printf("\\t");	/* HORIZONTAL TAB */
			break;

		case 0x0B:
			acpi_os_printf("\\v");	/* VERTICAL TAB */
			break;

		case '\'':	/* Single Quote */
		case '\"':	/* Double Quote */
		case '\\':	/* Backslash */
			acpi_os_printf("\\%c", (int)string[i]);
			break;

		default:

			/* Check for printable character or hex escape */

			if (ACPI_IS_PRINT(string[i])) {
				/* This is a normal character */

				acpi_os_printf("%c", (int)string[i]);
			} else {
				/* All others will be Hex escapes */

				acpi_os_printf("\\x%2.2X", (s32) string[i]);
			}
			break;
		}
	}
	acpi_os_printf("\"");

	if (i == max_length && string[i]) {
		acpi_os_printf("...");
	}
}