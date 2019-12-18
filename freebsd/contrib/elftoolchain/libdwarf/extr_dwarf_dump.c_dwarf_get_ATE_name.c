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

/* Variables and functions */
#define  DW_ATE_address 144 
#define  DW_ATE_boolean 143 
#define  DW_ATE_complex_float 142 
#define  DW_ATE_decimal_float 141 
#define  DW_ATE_edited 140 
#define  DW_ATE_float 139 
#define  DW_ATE_hi_user 138 
#define  DW_ATE_imaginary_float 137 
#define  DW_ATE_lo_user 136 
#define  DW_ATE_numeric_string 135 
#define  DW_ATE_packed_decimal 134 
#define  DW_ATE_signed 133 
#define  DW_ATE_signed_char 132 
#define  DW_ATE_signed_fixed 131 
#define  DW_ATE_unsigned 130 
#define  DW_ATE_unsigned_char 129 
#define  DW_ATE_unsigned_fixed 128 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_ATE_name(unsigned ate, const char **s)
{

	assert(s != NULL);

	switch(ate) {
	case DW_ATE_address:
		*s = "DW_ATE_address"; break;
	case DW_ATE_boolean:
		*s = "DW_ATE_boolean"; break;
	case DW_ATE_complex_float:
		*s = "DW_ATE_complex_float"; break;
	case DW_ATE_float:
		*s = "DW_ATE_float"; break;
	case DW_ATE_signed:
		*s = "DW_ATE_signed"; break;
	case DW_ATE_signed_char:
		*s = "DW_ATE_signed_char"; break;
	case DW_ATE_unsigned:
		*s = "DW_ATE_unsigned"; break;
	case DW_ATE_unsigned_char:
		*s = "DW_ATE_unsigned_char"; break;
	case DW_ATE_imaginary_float:
		*s = "DW_ATE_imaginary_float"; break;
	case DW_ATE_packed_decimal:
		*s = "DW_ATE_packed_decimal"; break;
	case DW_ATE_numeric_string:
		*s = "DW_ATE_numeric_string"; break;
	case DW_ATE_edited:
		*s = "DW_ATE_edited"; break;
	case DW_ATE_signed_fixed:
		*s = "DW_ATE_signed_fixed"; break;
	case DW_ATE_unsigned_fixed:
		*s = "DW_ATE_unsigned_fixed"; break;
	case DW_ATE_decimal_float:
		*s = "DW_ATE_decimal_float"; break;
	case DW_ATE_lo_user:
		*s = "DW_ATE_lo_user"; break;
	case DW_ATE_hi_user:
		*s = "DW_ATE_hi_user"; break;
	default:
		return (DW_DLV_NO_ENTRY);
	}

	return (DW_DLV_OK);
}