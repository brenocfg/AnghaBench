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
#define  DW_LNS_advance_line 139 
#define  DW_LNS_advance_pc 138 
#define  DW_LNS_const_add_pc 137 
#define  DW_LNS_copy 136 
#define  DW_LNS_fixed_advance_pc 135 
#define  DW_LNS_negate_stmt 134 
#define  DW_LNS_set_basic_block 133 
#define  DW_LNS_set_column 132 
#define  DW_LNS_set_epilogue_begin 131 
#define  DW_LNS_set_file 130 
#define  DW_LNS_set_isa 129 
#define  DW_LNS_set_prologue_end 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_LNS_name(unsigned lns, const char **s)
{

	assert(s != NULL);

	switch (lns) {
	case DW_LNS_copy:
		*s = "DW_LNS_copy"; break;
	case DW_LNS_advance_pc:
		*s = "DW_LNS_advance_pc"; break;
	case DW_LNS_advance_line:
		*s = "DW_LNS_advance_line"; break;
	case DW_LNS_set_file:
		*s = "DW_LNS_set_file"; break;
	case DW_LNS_set_column:
		*s = "DW_LNS_set_column"; break;
	case DW_LNS_negate_stmt:
		*s = "DW_LNS_negate_stmt"; break;
	case DW_LNS_set_basic_block:
		*s = "DW_LNS_set_basic_block"; break;
	case DW_LNS_const_add_pc:
		*s = "DW_LNS_const_add_pc"; break;
	case DW_LNS_fixed_advance_pc:
		*s = "DW_LNS_fixed_advance_pc"; break;
	case DW_LNS_set_prologue_end:
		*s = "DW_LNS_set_prologue_end"; break;
	case DW_LNS_set_epilogue_begin:
		*s = "DW_LNS_set_epilogue_begin"; break;
	case DW_LNS_set_isa:
		*s = "DW_LNS_set_isa"; break;
	default:
		return (DW_DLV_NO_ENTRY);
	}

	return (DW_DLV_OK);
}