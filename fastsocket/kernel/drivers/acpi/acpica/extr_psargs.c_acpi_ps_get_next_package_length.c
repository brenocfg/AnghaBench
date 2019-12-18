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
struct acpi_parse_state {int* aml; } ;
typedef  scalar_t__ acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps_get_next_package_length ; 
 int /*<<< orphan*/  return_UINT32 (int) ; 

__attribute__((used)) static u32
acpi_ps_get_next_package_length(struct acpi_parse_state *parser_state)
{
	u8 *aml = parser_state->aml;
	u32 package_length = 0;
	u32 byte_count;
	u8 byte_zero_mask = 0x3F;	/* Default [0:5] */

	ACPI_FUNCTION_TRACE(ps_get_next_package_length);

	/*
	 * Byte 0 bits [6:7] contain the number of additional bytes
	 * used to encode the package length, either 0,1,2, or 3
	 */
	byte_count = (aml[0] >> 6);
	parser_state->aml += ((acpi_size) byte_count + 1);

	/* Get bytes 3, 2, 1 as needed */

	while (byte_count) {
		/*
		 * Final bit positions for the package length bytes:
		 *      Byte3->[20:27]
		 *      Byte2->[12:19]
		 *      Byte1->[04:11]
		 *      Byte0->[00:03]
		 */
		package_length |= (aml[byte_count] << ((byte_count << 3) - 4));

		byte_zero_mask = 0x0F;	/* Use bits [0:3] of byte 0 */
		byte_count--;
	}

	/* Byte 0 is a special case, either bits [0:3] or [0:5] are used */

	package_length |= (aml[0] & byte_zero_mask);
	return_UINT32(package_length);
}