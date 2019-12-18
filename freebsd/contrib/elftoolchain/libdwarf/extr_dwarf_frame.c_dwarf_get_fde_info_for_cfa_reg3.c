#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dw_block_ptr; int /*<<< orphan*/  dw_offset_or_block_len; int /*<<< orphan*/  dw_regnum; int /*<<< orphan*/  dw_offset_relevant; int /*<<< orphan*/  dw_value_type; } ;
struct TYPE_5__ {scalar_t__ fde_initloc; scalar_t__ fde_adrange; int /*<<< orphan*/ * fde_dbg; } ;
typedef  int /*<<< orphan*/  Dwarf_Small ;
typedef  int /*<<< orphan*/  Dwarf_Signed ;
typedef  int /*<<< orphan*/  Dwarf_Regtable3 ;
typedef  int /*<<< orphan*/  Dwarf_Ptr ;
typedef  TYPE_1__* Dwarf_Fde ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  scalar_t__ Dwarf_Addr ;

/* Variables and functions */
 TYPE_4__ CFA ; 
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int DW_DLE_NONE ; 
 int /*<<< orphan*/  DW_DLE_PC_NOT_IN_FDE_RANGE ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
 int _dwarf_frame_get_internal_table (TYPE_1__*,scalar_t__,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ *) ; 

int
dwarf_get_fde_info_for_cfa_reg3(Dwarf_Fde fde, Dwarf_Addr pc_requested,
    Dwarf_Small *value_type, Dwarf_Signed *offset_relevant,
    Dwarf_Signed *register_num, Dwarf_Signed *offset_or_block_len,
    Dwarf_Ptr *block_ptr, Dwarf_Addr *row_pc, Dwarf_Error *error)
{
	Dwarf_Regtable3 *rt;
	Dwarf_Debug dbg;
	Dwarf_Addr pc;
	int ret;

	dbg = fde != NULL ? fde->fde_dbg : NULL;

	if (fde == NULL || value_type == NULL || offset_relevant == NULL ||
	    register_num == NULL || offset_or_block_len == NULL ||
	    block_ptr == NULL || row_pc == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	if (pc_requested < fde->fde_initloc ||
	    pc_requested >= fde->fde_initloc + fde->fde_adrange) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_PC_NOT_IN_FDE_RANGE);
		return (DW_DLV_ERROR);
	}

	ret = _dwarf_frame_get_internal_table(fde, pc_requested, &rt, &pc,
	    error);
	if (ret != DW_DLE_NONE)
		return (DW_DLV_ERROR);

	*value_type = CFA.dw_value_type;
	*offset_relevant = CFA.dw_offset_relevant;
	*register_num = CFA.dw_regnum;
	*offset_or_block_len = CFA.dw_offset_or_block_len;
	*block_ptr = CFA.dw_block_ptr;
	*row_pc = pc;

	return (DW_DLV_OK);
}