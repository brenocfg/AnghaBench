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
typedef  size_t u8 ;
typedef  size_t u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  acpi_integer ;

/* Variables and functions */
 size_t ACPI_ASCII_ZERO ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 size_t ACPI_MAX32_DECIMAL_DIGITS ; 
 size_t ACPI_MAX64_DECIMAL_DIGITS ; 
 size_t ACPI_MAX8_DECIMAL_DIGITS ; 
 size_t ACPI_MUL_2 (size_t) ; 
 int /*<<< orphan*/  ACPI_MUL_4 (size_t) ; 
 size_t FALSE ; 
 size_t TRUE ; 
 int /*<<< orphan*/  acpi_ut_hex_to_ascii_char (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_short_divide (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static u32
acpi_ex_convert_to_ascii(acpi_integer integer,
			 u16 base, u8 * string, u8 data_width)
{
	acpi_integer digit;
	u32 i;
	u32 j;
	u32 k = 0;
	u32 hex_length;
	u32 decimal_length;
	u32 remainder;
	u8 supress_zeros;

	ACPI_FUNCTION_ENTRY();

	switch (base) {
	case 10:

		/* Setup max length for the decimal number */

		switch (data_width) {
		case 1:
			decimal_length = ACPI_MAX8_DECIMAL_DIGITS;
			break;

		case 4:
			decimal_length = ACPI_MAX32_DECIMAL_DIGITS;
			break;

		case 8:
		default:
			decimal_length = ACPI_MAX64_DECIMAL_DIGITS;
			break;
		}

		supress_zeros = TRUE;	/* No leading zeros */
		remainder = 0;

		for (i = decimal_length; i > 0; i--) {

			/* Divide by nth factor of 10 */

			digit = integer;
			for (j = 0; j < i; j++) {
				(void)acpi_ut_short_divide(digit, 10, &digit,
							   &remainder);
			}

			/* Handle leading zeros */

			if (remainder != 0) {
				supress_zeros = FALSE;
			}

			if (!supress_zeros) {
				string[k] = (u8) (ACPI_ASCII_ZERO + remainder);
				k++;
			}
		}
		break;

	case 16:

		/* hex_length: 2 ascii hex chars per data byte */

		hex_length = ACPI_MUL_2(data_width);
		for (i = 0, j = (hex_length - 1); i < hex_length; i++, j--) {

			/* Get one hex digit, most significant digits first */

			string[k] =
			    (u8) acpi_ut_hex_to_ascii_char(integer,
							   ACPI_MUL_4(j));
			k++;
		}
		break;

	default:
		return (0);
	}

	/*
	 * Since leading zeros are suppressed, we must check for the case where
	 * the integer equals 0
	 *
	 * Finally, null terminate the string and return the length
	 */
	if (!k) {
		string[0] = ACPI_ASCII_ZERO;
		k = 1;
	}

	string[k] = 0;
	return ((u32) k);
}