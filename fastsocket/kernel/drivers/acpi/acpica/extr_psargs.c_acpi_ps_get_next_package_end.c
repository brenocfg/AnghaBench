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
typedef  int u32 ;
struct acpi_parse_state {int /*<<< orphan*/ * aml; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int acpi_ps_get_next_package_length (struct acpi_parse_state*) ; 
 int /*<<< orphan*/  ps_get_next_package_end ; 
 int /*<<< orphan*/  return_PTR (int /*<<< orphan*/ *) ; 

u8 *acpi_ps_get_next_package_end(struct acpi_parse_state *parser_state)
{
	u8 *start = parser_state->aml;
	u32 package_length;

	ACPI_FUNCTION_TRACE(ps_get_next_package_end);

	/* Function below updates parser_state->Aml */

	package_length = acpi_ps_get_next_package_length(parser_state);

	return_PTR(start + package_length);	/* end of package */
}