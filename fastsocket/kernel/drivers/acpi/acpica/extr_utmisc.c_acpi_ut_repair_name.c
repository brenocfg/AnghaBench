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
typedef  int u32 ;
typedef  int acpi_name ;

/* Variables and functions */
 int ACPI_NAME_SIZE ; 
 int /*<<< orphan*/  acpi_ut_valid_acpi_char (char,int) ; 

acpi_name acpi_ut_repair_name(char *name)
{
       u32 i;
	char new_name[ACPI_NAME_SIZE];

	for (i = 0; i < ACPI_NAME_SIZE; i++) {
		new_name[i] = name[i];

		/*
		 * Replace a bad character with something printable, yet technically
		 * still invalid. This prevents any collisions with existing "good"
		 * names in the namespace.
		 */
		if (!acpi_ut_valid_acpi_char(name[i], i)) {
			new_name[i] = '*';
		}
	}

	return (*(u32 *) new_name);
}