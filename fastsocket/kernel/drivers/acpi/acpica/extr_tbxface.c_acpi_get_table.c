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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_table_header {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_get_table_with_size (char*,int /*<<< orphan*/ ,struct acpi_table_header**,int /*<<< orphan*/ *) ; 

acpi_status
acpi_get_table(char *signature,
	       u32 instance, struct acpi_table_header **out_table)
{
	acpi_size tbl_size;

	return acpi_get_table_with_size(signature,
		       instance, out_table, &tbl_size);
}