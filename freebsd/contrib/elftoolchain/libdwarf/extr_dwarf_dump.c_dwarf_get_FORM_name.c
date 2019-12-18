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
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
#define  DW_FORM_addr 152 
#define  DW_FORM_block 151 
#define  DW_FORM_block1 150 
#define  DW_FORM_block2 149 
#define  DW_FORM_block4 148 
#define  DW_FORM_data1 147 
#define  DW_FORM_data2 146 
#define  DW_FORM_data4 145 
#define  DW_FORM_data8 144 
#define  DW_FORM_exprloc 143 
#define  DW_FORM_flag 142 
#define  DW_FORM_flag_present 141 
#define  DW_FORM_indirect 140 
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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_FORM_name(unsigned form, const char **s)
{

	assert(s != NULL);

	switch (form) {
	case DW_FORM_addr:
		*s = "DW_FORM_addr"; break;
	case DW_FORM_block:
		*s = "DW_FORM_block"; break;
	case DW_FORM_block1:
		*s = "DW_FORM_block1"; break;
	case DW_FORM_block2:
		*s = "DW_FORM_block2"; break;
	case DW_FORM_block4:
		*s = "DW_FORM_block4"; break;
	case DW_FORM_data1:
		*s = "DW_FORM_data1"; break;
	case DW_FORM_data2:
		*s = "DW_FORM_data2"; break;
	case DW_FORM_data4:
		*s = "DW_FORM_data4"; break;
	case DW_FORM_data8:
		*s = "DW_FORM_data8"; break;
	case DW_FORM_exprloc:
		*s = "DW_FORM_exprloc"; break;
	case DW_FORM_flag:
		*s = "DW_FORM_flag"; break;
	case DW_FORM_flag_present:
		*s = "DW_FORM_flag_present"; break;
	case DW_FORM_indirect:
		*s = "DW_FORM_indirect"; break;
	case DW_FORM_ref1:
		*s = "DW_FORM_ref1"; break;
	case DW_FORM_ref2:
		*s = "DW_FORM_ref2"; break;
	case DW_FORM_ref4:
		*s = "DW_FORM_ref4"; break;
	case DW_FORM_ref8:
		*s = "DW_FORM_ref8"; break;
	case DW_FORM_ref_addr:
		*s = "DW_FORM_ref_addr"; break;
	case DW_FORM_ref_sig8:
		*s = "DW_FORM_ref_sig8"; break;
	case DW_FORM_ref_udata:
		*s = "DW_FORM_ref_udata"; break;
	case DW_FORM_sdata:
		*s = "DW_FORM_sdata"; break;
	case DW_FORM_sec_offset:
		*s = "DW_FORM_sec_offset"; break;
	case DW_FORM_string:
		*s = "DW_FORM_string"; break;
	case DW_FORM_strp:
		*s = "DW_FORM_strp"; break;
	case DW_FORM_udata:
		*s = "DW_FORM_udata"; break;
	default:
		return (DW_DLV_NO_ENTRY);
	}

	return (DW_DLV_OK);
}