#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ fde_initloc; scalar_t__ fde_adrange; int /*<<< orphan*/ * fde_dbg; } ;
struct TYPE_9__ {int /*<<< orphan*/ * rt3_rules; } ;
typedef  TYPE_1__ Dwarf_Regtable3 ;
typedef  TYPE_2__* Dwarf_Fde ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  scalar_t__ Dwarf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int DW_DLE_NONE ; 
 int /*<<< orphan*/  DW_DLE_PC_NOT_IN_FDE_RANGE ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
 int _dwarf_frame_get_internal_table (TYPE_2__*,scalar_t__,TYPE_1__**,scalar_t__*,int /*<<< orphan*/ *) ; 
 int _dwarf_frame_regtable_copy (int /*<<< orphan*/ *,TYPE_1__**,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_fde_info_for_all_regs3(Dwarf_Fde fde, Dwarf_Addr pc_requested,
    Dwarf_Regtable3 *reg_table, Dwarf_Addr *row_pc, Dwarf_Error *error)
{
	Dwarf_Regtable3 *rt;
	Dwarf_Debug dbg;
	Dwarf_Addr pc;
	int ret;

	dbg = fde != NULL ? fde->fde_dbg : NULL;

	if (fde == NULL || reg_table == NULL || reg_table->rt3_rules == NULL ||
	    row_pc == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	assert(dbg != NULL);

	if (pc_requested < fde->fde_initloc ||
	    pc_requested >= fde->fde_initloc + fde->fde_adrange) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_PC_NOT_IN_FDE_RANGE);
		return (DW_DLV_ERROR);
	}

	ret = _dwarf_frame_get_internal_table(fde, pc_requested, &rt, &pc,
	    error);
	if (ret != DW_DLE_NONE)
		return (DW_DLV_ERROR);

	ret = _dwarf_frame_regtable_copy(dbg, &reg_table, rt, error);
	if (ret != DW_DLE_NONE)
		return (DW_DLV_ERROR);

	*row_pc = pc;

	return (DW_DLV_OK);
}