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
#define  DW_CFA_advance_loc 155 
#define  DW_CFA_advance_loc1 154 
#define  DW_CFA_advance_loc2 153 
#define  DW_CFA_advance_loc4 152 
#define  DW_CFA_def_cfa 151 
#define  DW_CFA_def_cfa_expression 150 
#define  DW_CFA_def_cfa_offset 149 
#define  DW_CFA_def_cfa_offset_sf 148 
#define  DW_CFA_def_cfa_register 147 
#define  DW_CFA_def_cfa_sf 146 
#define  DW_CFA_expression 145 
#define  DW_CFA_high_user 144 
#define  DW_CFA_lo_user 143 
#define  DW_CFA_nop 142 
#define  DW_CFA_offset 141 
#define  DW_CFA_offset_extended 140 
#define  DW_CFA_offset_extended_sf 139 
#define  DW_CFA_register 138 
#define  DW_CFA_remember_state 137 
#define  DW_CFA_restore 136 
#define  DW_CFA_restore_extended 135 
#define  DW_CFA_restore_state 134 
#define  DW_CFA_same_value 133 
#define  DW_CFA_set_loc 132 
#define  DW_CFA_undefined 131 
#define  DW_CFA_val_expression 130 
#define  DW_CFA_val_offset 129 
#define  DW_CFA_val_offset_sf 128 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_CFA_name(unsigned cfa, const char **s)
{

	assert(s != NULL);

	switch (cfa) {
	case DW_CFA_advance_loc:
		*s = "DW_CFA_advance_loc"; break;
	case DW_CFA_offset:
		*s = "DW_CFA_offset"; break;
	case DW_CFA_restore:
		*s = "DW_CFA_restore"; break;
	case DW_CFA_nop:
		*s = "DW_CFA_nop"; break;
	case DW_CFA_set_loc:
		*s = "DW_CFA_set_loc"; break;
	case DW_CFA_advance_loc1:
		*s = "DW_CFA_advance_loc1"; break;
	case DW_CFA_advance_loc2:
		*s = "DW_CFA_advance_loc2"; break;
	case DW_CFA_advance_loc4:
		*s = "DW_CFA_advance_loc4"; break;
	case DW_CFA_offset_extended:
		*s = "DW_CFA_offset_extended"; break;
	case DW_CFA_restore_extended:
		*s = "DW_CFA_restore_extended"; break;
	case DW_CFA_undefined:
		*s = "DW_CFA_undefined"; break;
	case DW_CFA_same_value:
		*s = "DW_CFA_same_value"; break;
	case DW_CFA_register:
		*s = "DW_CFA_register"; break;
	case DW_CFA_remember_state:
		*s = "DW_CFA_remember_state"; break;
	case DW_CFA_restore_state:
		*s = "DW_CFA_restore_state"; break;
	case DW_CFA_def_cfa:
		*s = "DW_CFA_def_cfa"; break;
	case DW_CFA_def_cfa_register:
		*s = "DW_CFA_def_cfa_register"; break;
	case DW_CFA_def_cfa_offset:
		*s = "DW_CFA_def_cfa_offset"; break;
	case DW_CFA_def_cfa_expression:
		*s = "DW_CFA_def_cfa_expression"; break;
	case DW_CFA_expression:
		*s = "DW_CFA_expression"; break;
	case DW_CFA_offset_extended_sf:
		*s = "DW_CFA_offset_extended_sf"; break;
	case DW_CFA_def_cfa_sf:
		*s = "DW_CFA_def_cfa_sf"; break;
	case DW_CFA_def_cfa_offset_sf:
		*s = "DW_CFA_def_cfa_offset_sf"; break;
	case DW_CFA_val_offset:
		*s = "DW_CFA_val_offset"; break;
	case DW_CFA_val_offset_sf:
		*s = "DW_CFA_val_offset_sf"; break;
	case DW_CFA_val_expression:
		*s = "DW_CFA_val_expression"; break;
	case DW_CFA_lo_user:
		*s = "DW_CFA_lo_user"; break;
	case DW_CFA_high_user:
		*s = "DW_CFA_high_user"; break;
	default:
		return (DW_DLV_NO_ENTRY);
	}

	return (DW_DLV_OK);
}