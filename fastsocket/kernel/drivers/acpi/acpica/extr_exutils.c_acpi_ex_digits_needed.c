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
typedef  scalar_t__ acpi_integer ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_short_divide (scalar_t__,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ex_digits_needed ; 
 int /*<<< orphan*/  return_UINT32 (int) ; 

__attribute__((used)) static u32 acpi_ex_digits_needed(acpi_integer value, u32 base)
{
	u32 num_digits;
	acpi_integer current_value;

	ACPI_FUNCTION_TRACE(ex_digits_needed);

	/* acpi_integer is unsigned, so we don't worry about a '-' prefix */

	if (value == 0) {
		return_UINT32(1);
	}

	current_value = value;
	num_digits = 0;

	/* Count the digits in the requested base */

	while (current_value) {
		(void)acpi_ut_short_divide(current_value, base, &current_value,
					   NULL);
		num_digits++;
	}

	return_UINT32(num_digits);
}