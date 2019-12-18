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
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int hex_val (char) ; 
 int /*<<< orphan*/  isxdigit (char) ; 
 int strlen (char*) ; 

__attribute__((used)) static acpi_status acpi_str_to_uuid(char *str, u8 *uuid)
{
	int i;
	static int opc_map_to_uuid[16] = {6, 4, 2, 0, 11, 9, 16, 14, 19, 21,
		24, 26, 28, 30, 32, 34};

	if (strlen(str) != 36)
		return AE_BAD_PARAMETER;
	for (i = 0; i < 36; i++) {
		if (i == 8 || i == 13 || i == 18 || i == 23) {
			if (str[i] != '-')
				return AE_BAD_PARAMETER;
		} else if (!isxdigit(str[i]))
			return AE_BAD_PARAMETER;
	}
	for (i = 0; i < 16; i++) {
		uuid[i] = hex_val(str[opc_map_to_uuid[i]]) << 4;
		uuid[i] |= hex_val(str[opc_map_to_uuid[i] + 1]);
	}
	return AE_OK;
}