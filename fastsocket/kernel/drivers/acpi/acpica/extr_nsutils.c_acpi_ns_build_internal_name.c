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
struct acpi_namestring_info {int num_segments; char* internal_name; char* next_external_char; int num_carats; scalar_t__ fully_qualified; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  size_t acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_NAME_SIZE ; 
 scalar_t__ ACPI_TOUPPER (int) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 char AML_DUAL_NAME_PREFIX ; 
 char AML_MULTI_NAME_PREFIX_OP ; 
 scalar_t__ acpi_ns_valid_path_separator (char const) ; 
 int /*<<< orphan*/  ns_build_internal_name ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ns_build_internal_name(struct acpi_namestring_info *info)
{
	u32 num_segments = info->num_segments;
	char *internal_name = info->internal_name;
	const char *external_name = info->next_external_char;
	char *result = NULL;
	u32 i;

	ACPI_FUNCTION_TRACE(ns_build_internal_name);

	/* Setup the correct prefixes, counts, and pointers */

	if (info->fully_qualified) {
		internal_name[0] = '\\';

		if (num_segments <= 1) {
			result = &internal_name[1];
		} else if (num_segments == 2) {
			internal_name[1] = AML_DUAL_NAME_PREFIX;
			result = &internal_name[2];
		} else {
			internal_name[1] = AML_MULTI_NAME_PREFIX_OP;
			internal_name[2] = (char)num_segments;
			result = &internal_name[3];
		}
	} else {
		/*
		 * Not fully qualified.
		 * Handle Carats first, then append the name segments
		 */
		i = 0;
		if (info->num_carats) {
			for (i = 0; i < info->num_carats; i++) {
				internal_name[i] = '^';
			}
		}

		if (num_segments <= 1) {
			result = &internal_name[i];
		} else if (num_segments == 2) {
			internal_name[i] = AML_DUAL_NAME_PREFIX;
			result = &internal_name[(acpi_size) i + 1];
		} else {
			internal_name[i] = AML_MULTI_NAME_PREFIX_OP;
			internal_name[(acpi_size) i + 1] = (char)num_segments;
			result = &internal_name[(acpi_size) i + 2];
		}
	}

	/* Build the name (minus path separators) */

	for (; num_segments; num_segments--) {
		for (i = 0; i < ACPI_NAME_SIZE; i++) {
			if (acpi_ns_valid_path_separator(*external_name) ||
			    (*external_name == 0)) {

				/* Pad the segment with underscore(s) if segment is short */

				result[i] = '_';
			} else {
				/* Convert the character to uppercase and save it */

				result[i] =
				    (char)ACPI_TOUPPER((int)*external_name);
				external_name++;
			}
		}

		/* Now we must have a path separator, or the pathname is bad */

		if (!acpi_ns_valid_path_separator(*external_name) &&
		    (*external_name != 0)) {
			return_ACPI_STATUS(AE_BAD_PARAMETER);
		}

		/* Move on the next segment */

		external_name++;
		result += ACPI_NAME_SIZE;
	}

	/* Terminate the string */

	*result = 0;

	if (info->fully_qualified) {
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "Returning [%p] (abs) \"\\%s\"\n",
				  internal_name, internal_name));
	} else {
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Returning [%p] (rel) \"%s\"\n",
				  internal_name, internal_name));
	}

	return_ACPI_STATUS(AE_OK);
}