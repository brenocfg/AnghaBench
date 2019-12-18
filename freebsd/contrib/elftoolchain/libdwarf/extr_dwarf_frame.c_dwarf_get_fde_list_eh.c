#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* dbg_eh_frame; int /*<<< orphan*/ * dbg_internal_reg_table; } ;
struct TYPE_7__ {int /*<<< orphan*/  fs_fdelen; int /*<<< orphan*/ * fs_fdearray; int /*<<< orphan*/  fs_cielen; int /*<<< orphan*/ * fs_ciearray; } ;
typedef  int /*<<< orphan*/  Dwarf_Signed ;
typedef  int /*<<< orphan*/  Dwarf_Fde ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_2__* Dwarf_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Cie ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 scalar_t__ DW_DLE_NONE ; 
 int /*<<< orphan*/  DW_DLE_NO_ENTRY ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
 scalar_t__ _dwarf_frame_interal_table_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ _dwarf_frame_section_load_eh (TYPE_2__*,int /*<<< orphan*/ *) ; 

int
dwarf_get_fde_list_eh(Dwarf_Debug dbg, Dwarf_Cie **cie_list,
    Dwarf_Signed *cie_count, Dwarf_Fde **fde_list, Dwarf_Signed *fde_count,
    Dwarf_Error *error)
{

	if (dbg == NULL || cie_list == NULL || cie_count == NULL ||
	    fde_list == NULL || fde_count == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	if (dbg->dbg_internal_reg_table == NULL) {
		if (_dwarf_frame_interal_table_init(dbg, error) != DW_DLE_NONE)
			return (DW_DLV_ERROR);
	}

	if (dbg->dbg_eh_frame == NULL) {
		if (_dwarf_frame_section_load_eh(dbg, error) != DW_DLE_NONE)
			return (DW_DLV_ERROR);
		if (dbg->dbg_eh_frame == NULL) {
			DWARF_SET_ERROR(dbg, error, DW_DLE_NO_ENTRY);
			return (DW_DLV_NO_ENTRY);
		}
	}

	if (dbg->dbg_eh_frame->fs_ciearray == NULL ||
	    dbg->dbg_eh_frame->fs_fdearray == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_NO_ENTRY);
		return (DW_DLV_NO_ENTRY);
	}

	*cie_list = dbg->dbg_eh_frame->fs_ciearray;
	*cie_count = dbg->dbg_eh_frame->fs_cielen;
	*fde_list = dbg->dbg_eh_frame->fs_fdearray;
	*fde_count = dbg->dbg_eh_frame->fs_fdelen;

	return (DW_DLV_OK);
}