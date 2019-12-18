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
typedef  size_t u32 ;
struct acpi_namestring_info {char* external_name; int num_segments; char const* next_external_char; scalar_t__ num_carats; scalar_t__ length; int /*<<< orphan*/  fully_qualified; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int ACPI_NAME_SIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ acpi_ns_valid_path_separator (char const) ; 
 scalar_t__ acpi_ns_valid_root_prefix (char const) ; 

void acpi_ns_get_internal_name_length(struct acpi_namestring_info *info)
{
	const char *next_external_char;
	u32 i;

	ACPI_FUNCTION_ENTRY();

	next_external_char = info->external_name;
	info->num_carats = 0;
	info->num_segments = 0;
	info->fully_qualified = FALSE;

	/*
	 * For the internal name, the required length is 4 bytes per segment, plus
	 * 1 each for root_prefix, multi_name_prefix_op, segment count, trailing null
	 * (which is not really needed, but no there's harm in putting it there)
	 *
	 * strlen() + 1 covers the first name_seg, which has no path separator
	 */
	if (acpi_ns_valid_root_prefix(*next_external_char)) {
		info->fully_qualified = TRUE;
		next_external_char++;

		/* Skip redundant root_prefix, like \\_SB.PCI0.SBRG.EC0 */

		while (acpi_ns_valid_root_prefix(*next_external_char)) {
			next_external_char++;
		}
	} else {
		/* Handle Carat prefixes */

		while (*next_external_char == '^') {
			info->num_carats++;
			next_external_char++;
		}
	}

	/*
	 * Determine the number of ACPI name "segments" by counting the number of
	 * path separators within the string. Start with one segment since the
	 * segment count is [(# separators) + 1], and zero separators is ok.
	 */
	if (*next_external_char) {
		info->num_segments = 1;
		for (i = 0; next_external_char[i]; i++) {
			if (acpi_ns_valid_path_separator(next_external_char[i])) {
				info->num_segments++;
			}
		}
	}

	info->length = (ACPI_NAME_SIZE * info->num_segments) +
	    4 + info->num_carats;

	info->next_external_char = next_external_char;
}