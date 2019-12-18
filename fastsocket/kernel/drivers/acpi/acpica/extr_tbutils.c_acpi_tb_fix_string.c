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
typedef  scalar_t__ acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_IS_PRINT (char) ; 

__attribute__((used)) static void acpi_tb_fix_string(char *string, acpi_size length)
{

	while (length && *string) {
		if (!ACPI_IS_PRINT(*string)) {
			*string = '?';
		}
		string++;
		length--;
	}
}