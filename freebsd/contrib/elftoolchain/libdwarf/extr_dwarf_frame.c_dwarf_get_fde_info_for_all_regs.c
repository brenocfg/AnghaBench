#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_19__ {size_t dbg_frame_cfa_value; int dbg_frame_rule_table_size; } ;
struct TYPE_18__ {scalar_t__ fde_initloc; scalar_t__ fde_adrange; TYPE_6__* fde_dbg; } ;
struct TYPE_17__ {TYPE_1__* rules; } ;
struct TYPE_16__ {TYPE_2__* rt3_rules; } ;
struct TYPE_15__ {int /*<<< orphan*/  dw_offset_or_block_len; int /*<<< orphan*/  dw_regnum; int /*<<< orphan*/  dw_offset_relevant; } ;
struct TYPE_14__ {int /*<<< orphan*/  dw_offset; int /*<<< orphan*/  dw_regnum; int /*<<< orphan*/  dw_offset_relevant; } ;
struct TYPE_13__ {int /*<<< orphan*/  dw_offset_or_block_len; int /*<<< orphan*/  dw_regnum; int /*<<< orphan*/  dw_offset_relevant; } ;
typedef  TYPE_3__ Dwarf_Regtable3 ;
typedef  TYPE_4__ Dwarf_Regtable ;
typedef  size_t Dwarf_Half ;
typedef  TYPE_5__* Dwarf_Fde ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_6__* Dwarf_Debug ;
typedef  scalar_t__ Dwarf_Addr ;

/* Variables and functions */
 TYPE_12__ CFA ; 
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int DW_DLE_NONE ; 
 int /*<<< orphan*/  DW_DLE_PC_NOT_IN_FDE_RANGE ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
 size_t DW_REG_TABLE_SIZE ; 
 int _dwarf_frame_get_internal_table (TYPE_5__*,scalar_t__,TYPE_3__**,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_fde_info_for_all_regs(Dwarf_Fde fde, Dwarf_Addr pc_requested,
    Dwarf_Regtable *reg_table, Dwarf_Addr *row_pc, Dwarf_Error *error)
{
	Dwarf_Debug dbg;
	Dwarf_Regtable3 *rt;
	Dwarf_Addr pc;
	Dwarf_Half cfa;
	int i, ret;

	dbg = fde != NULL ? fde->fde_dbg : NULL;

	if (fde == NULL || reg_table == NULL || row_pc == NULL) {
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

	/*
	 * Copy the CFA rule to the column intended for holding the CFA,
	 * if it's within the range of regtable.
	 */
	cfa = dbg->dbg_frame_cfa_value;
	if (cfa < DW_REG_TABLE_SIZE) {
		reg_table->rules[cfa].dw_offset_relevant =
		    CFA.dw_offset_relevant;
		reg_table->rules[cfa].dw_regnum = CFA.dw_regnum;
		reg_table->rules[cfa].dw_offset = CFA.dw_offset_or_block_len;
	}

	/*
	 * Copy other columns.
	 */
	for (i = 0; i < DW_REG_TABLE_SIZE && i < dbg->dbg_frame_rule_table_size;
	     i++) {

		/* Do not overwrite CFA column */
		if (i == cfa)
			continue;

		reg_table->rules[i].dw_offset_relevant =
		    rt->rt3_rules[i].dw_offset_relevant;
		reg_table->rules[i].dw_regnum = rt->rt3_rules[i].dw_regnum;
		reg_table->rules[i].dw_offset =
		    rt->rt3_rules[i].dw_offset_or_block_len;
	}

	*row_pc = pc;

	return (DW_DLV_OK);
}