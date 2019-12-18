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
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ acpi_status ;
typedef  scalar_t__ acpi_object_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DB_LOAD ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ACPI_SUCCESS (scalar_t__) ; 
 scalar_t__ ACPI_TYPE_LOCAL_BANK_FIELD ; 
 scalar_t__ ACPI_TYPE_LOCAL_INDEX_FIELD ; 
 scalar_t__ ACPI_TYPE_LOCAL_REGION_FIELD ; 
 int ACPI_UINT32_MAX ; 
 scalar_t__ AE_AML_BAD_NAME ; 
 scalar_t__ AE_CTRL_PENDING ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_NO_MEMORY ; 
 scalar_t__ AE_OK ; 
#define  AML_DUAL_NAME_PREFIX 131 
#define  AML_MULTI_NAME_PREFIX_OP 130 
#define  AML_PARENT_PREFIX 129 
#define  AML_ROOT_PREFIX 128 
 int FALSE ; 
 int TRUE ; 
 char* acpi_ex_allocate_name_string (int,int) ; 
 scalar_t__ acpi_ex_name_segment (int**,char*) ; 
 int /*<<< orphan*/  ex_get_name_string ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

acpi_status
acpi_ex_get_name_string(acpi_object_type data_type,
			u8 * in_aml_address,
			char **out_name_string, u32 * out_name_length)
{
	acpi_status status = AE_OK;
	u8 *aml_address = in_aml_address;
	char *name_string = NULL;
	u32 num_segments;
	u32 prefix_count = 0;
	u8 has_prefix = FALSE;

	ACPI_FUNCTION_TRACE_PTR(ex_get_name_string, aml_address);

	if (ACPI_TYPE_LOCAL_REGION_FIELD == data_type ||
	    ACPI_TYPE_LOCAL_BANK_FIELD == data_type ||
	    ACPI_TYPE_LOCAL_INDEX_FIELD == data_type) {

		/* Disallow prefixes for types associated with field_unit names */

		name_string = acpi_ex_allocate_name_string(0, 1);
		if (!name_string) {
			status = AE_NO_MEMORY;
		} else {
			status =
			    acpi_ex_name_segment(&aml_address, name_string);
		}
	} else {
		/*
		 * data_type is not a field name.
		 * Examine first character of name for root or parent prefix operators
		 */
		switch (*aml_address) {
		case AML_ROOT_PREFIX:

			ACPI_DEBUG_PRINT((ACPI_DB_LOAD,
					  "RootPrefix(\\) at %p\n",
					  aml_address));

			/*
			 * Remember that we have a root_prefix --
			 * see comment in acpi_ex_allocate_name_string()
			 */
			aml_address++;
			prefix_count = ACPI_UINT32_MAX;
			has_prefix = TRUE;
			break;

		case AML_PARENT_PREFIX:

			/* Increment past possibly multiple parent prefixes */

			do {
				ACPI_DEBUG_PRINT((ACPI_DB_LOAD,
						  "ParentPrefix (^) at %p\n",
						  aml_address));

				aml_address++;
				prefix_count++;

			} while (*aml_address == AML_PARENT_PREFIX);

			has_prefix = TRUE;
			break;

		default:

			/* Not a prefix character */

			break;
		}

		/* Examine first character of name for name segment prefix operator */

		switch (*aml_address) {
		case AML_DUAL_NAME_PREFIX:

			ACPI_DEBUG_PRINT((ACPI_DB_LOAD,
					  "DualNamePrefix at %p\n",
					  aml_address));

			aml_address++;
			name_string =
			    acpi_ex_allocate_name_string(prefix_count, 2);
			if (!name_string) {
				status = AE_NO_MEMORY;
				break;
			}

			/* Indicate that we processed a prefix */

			has_prefix = TRUE;

			status =
			    acpi_ex_name_segment(&aml_address, name_string);
			if (ACPI_SUCCESS(status)) {
				status =
				    acpi_ex_name_segment(&aml_address,
							 name_string);
			}
			break;

		case AML_MULTI_NAME_PREFIX_OP:

			ACPI_DEBUG_PRINT((ACPI_DB_LOAD,
					  "MultiNamePrefix at %p\n",
					  aml_address));

			/* Fetch count of segments remaining in name path */

			aml_address++;
			num_segments = *aml_address;

			name_string =
			    acpi_ex_allocate_name_string(prefix_count,
							 num_segments);
			if (!name_string) {
				status = AE_NO_MEMORY;
				break;
			}

			/* Indicate that we processed a prefix */

			aml_address++;
			has_prefix = TRUE;

			while (num_segments &&
			       (status =
				acpi_ex_name_segment(&aml_address,
						     name_string)) == AE_OK) {
				num_segments--;
			}

			break;

		case 0:

			/* null_name valid as of 8-12-98 ASL/AML Grammar Update */

			if (prefix_count == ACPI_UINT32_MAX) {
				ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
						  "NameSeg is \"\\\" followed by NULL\n"));
			}

			/* Consume the NULL byte */

			aml_address++;
			name_string =
			    acpi_ex_allocate_name_string(prefix_count, 0);
			if (!name_string) {
				status = AE_NO_MEMORY;
				break;
			}

			break;

		default:

			/* Name segment string */

			name_string =
			    acpi_ex_allocate_name_string(prefix_count, 1);
			if (!name_string) {
				status = AE_NO_MEMORY;
				break;
			}

			status =
			    acpi_ex_name_segment(&aml_address, name_string);
			break;
		}
	}

	if (AE_CTRL_PENDING == status && has_prefix) {

		/* Ran out of segments after processing a prefix */

		ACPI_ERROR((AE_INFO, "Malformed Name at %p", name_string));
		status = AE_AML_BAD_NAME;
	}

	if (ACPI_FAILURE(status)) {
		if (name_string) {
			ACPI_FREE(name_string);
		}
		return_ACPI_STATUS(status);
	}

	*out_name_string = name_string;
	*out_name_length = (u32) (aml_address - in_aml_address);

	return_ACPI_STATUS(status);
}