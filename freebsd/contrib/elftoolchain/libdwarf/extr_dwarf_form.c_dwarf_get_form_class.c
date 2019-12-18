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
typedef  enum Dwarf_Form_Class { ____Placeholder_Dwarf_Form_Class } Dwarf_Form_Class ;
typedef  int Dwarf_Half ;

/* Variables and functions */
#define  DW_AT_data_member_location 164 
#define  DW_AT_frame_base 163 
#define  DW_AT_location 162 
#define  DW_AT_macro_info 161 
#define  DW_AT_ranges 160 
#define  DW_AT_return_addr 159 
#define  DW_AT_segment 158 
#define  DW_AT_start_scope 157 
#define  DW_AT_static_link 156 
#define  DW_AT_stmt_list 155 
#define  DW_AT_string_length 154 
#define  DW_AT_use_location 153 
#define  DW_AT_vtable_elem_location 152 
 int DW_FORM_CLASS_ADDRESS ; 
 int DW_FORM_CLASS_BLOCK ; 
 int DW_FORM_CLASS_CONSTANT ; 
 int DW_FORM_CLASS_EXPRLOC ; 
 int DW_FORM_CLASS_FLAG ; 
 int DW_FORM_CLASS_LINEPTR ; 
 int DW_FORM_CLASS_LOCLISTPTR ; 
 int DW_FORM_CLASS_MACPTR ; 
 int DW_FORM_CLASS_RANGELISTPTR ; 
 int DW_FORM_CLASS_REFERENCE ; 
 int DW_FORM_CLASS_STRING ; 
 int DW_FORM_CLASS_UNKNOWN ; 
#define  DW_FORM_addr 151 
#define  DW_FORM_block 150 
#define  DW_FORM_block1 149 
#define  DW_FORM_block2 148 
#define  DW_FORM_block4 147 
#define  DW_FORM_data1 146 
#define  DW_FORM_data2 145 
#define  DW_FORM_data4 144 
#define  DW_FORM_data8 143 
#define  DW_FORM_exprloc 142 
#define  DW_FORM_flag 141 
#define  DW_FORM_flag_present 140 
#define  DW_FORM_ref1 139 
#define  DW_FORM_ref2 138 
#define  DW_FORM_ref4 137 
#define  DW_FORM_ref8 136 
#define  DW_FORM_ref_addr 135 
#define  DW_FORM_ref_sig8 134 
#define  DW_FORM_ref_udata 133 
#define  DW_FORM_sdata 132 
#define  DW_FORM_sec_offset 131 
#define  DW_FORM_string 130 
#define  DW_FORM_strp 129 
#define  DW_FORM_udata 128 

enum Dwarf_Form_Class
dwarf_get_form_class(Dwarf_Half dwversion, Dwarf_Half attr,
    Dwarf_Half offset_size, Dwarf_Half form)
{

	switch (form) {
	case DW_FORM_addr:
		return (DW_FORM_CLASS_ADDRESS);
	case DW_FORM_block:
	case DW_FORM_block1:
	case DW_FORM_block2:
	case DW_FORM_block4:
		return (DW_FORM_CLASS_BLOCK);
	case DW_FORM_string:
	case DW_FORM_strp:
		return (DW_FORM_CLASS_STRING);
	case DW_FORM_flag:
	case DW_FORM_flag_present:
		return (DW_FORM_CLASS_FLAG);
	case DW_FORM_ref_addr:
	case DW_FORM_ref_sig8:
	case DW_FORM_ref_udata:
	case DW_FORM_ref1:
	case DW_FORM_ref2:
	case DW_FORM_ref4:
	case DW_FORM_ref8:
		return (DW_FORM_CLASS_REFERENCE);
	case DW_FORM_exprloc:
		return (DW_FORM_CLASS_EXPRLOC);
	case DW_FORM_data1:
	case DW_FORM_data2:
	case DW_FORM_sdata:
	case DW_FORM_udata:
		return (DW_FORM_CLASS_CONSTANT);
	case DW_FORM_data4:
	case DW_FORM_data8:
		if (dwversion > 3)
			return (DW_FORM_CLASS_CONSTANT);
		if (form == DW_FORM_data4 && offset_size != 4)
			return (DW_FORM_CLASS_CONSTANT);
		if (form == DW_FORM_data8 && offset_size != 8)
			return (DW_FORM_CLASS_CONSTANT);
		/* FALLTHROUGH */
	case DW_FORM_sec_offset:
		/*
		 * DW_FORM_data4 and DW_FORM_data8 can be used as
		 * offset/pointer before DWARF4. Newly added
		 * DWARF4 form DW_FORM_sec_offset intents to replace
		 * DW_FORM_data{4,8} for this purpose. Anyway, to
		 * determine the actual class for these forms, we need
		 * to also look at the attribute number.
		 */
		switch (attr) {
		case DW_AT_location:
		case DW_AT_string_length:
		case DW_AT_return_addr:
		case DW_AT_data_member_location:
		case DW_AT_frame_base:
		case DW_AT_segment:
		case DW_AT_static_link:
		case DW_AT_use_location:
		case DW_AT_vtable_elem_location:
			return (DW_FORM_CLASS_LOCLISTPTR);
		case DW_AT_stmt_list:
			return (DW_FORM_CLASS_LINEPTR);
		case DW_AT_start_scope:
		case DW_AT_ranges:
			return (DW_FORM_CLASS_RANGELISTPTR);
		case DW_AT_macro_info:
			return (DW_FORM_CLASS_MACPTR);
		default:
			if (form == DW_FORM_data4 || form == DW_FORM_data8)
				return (DW_FORM_CLASS_CONSTANT);
			else
				return (DW_FORM_CLASS_UNKNOWN);
		}
	default:
		return (DW_FORM_CLASS_UNKNOWN);
	}
}