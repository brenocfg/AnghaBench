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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ acpi_object_type ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_LOCAL_MAX ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

u8 acpi_ut_valid_object_type(acpi_object_type type)
{

	if (type > ACPI_TYPE_LOCAL_MAX) {

		/* Note: Assumes all TYPEs are contiguous (external/local) */

		return (FALSE);
	}

	return (TRUE);
}