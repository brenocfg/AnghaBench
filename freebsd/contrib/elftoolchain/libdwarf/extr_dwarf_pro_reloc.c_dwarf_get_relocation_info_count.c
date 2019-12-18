#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dbgp_flags; int /*<<< orphan*/  dbgp_drscnt; } ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  TYPE_1__* Dwarf_P_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int DWARF_DRD_BUFFER_VERSION ; 
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int DW_DLC_SYMBOLIC_RELOCATIONS ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int /*<<< orphan*/  DW_DLE_NO_ENTRY ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 

int
dwarf_get_relocation_info_count(Dwarf_P_Debug dbg, Dwarf_Unsigned *reloc_cnt,
    int *drd_buffer_version, Dwarf_Error *error)
{

	if (dbg == NULL || reloc_cnt == NULL || drd_buffer_version == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	if ((dbg->dbgp_flags & DW_DLC_SYMBOLIC_RELOCATIONS) == 0) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_NO_ENTRY);
		return (DW_DLV_NO_ENTRY);
	}

	*reloc_cnt = dbg->dbgp_drscnt;
	*drd_buffer_version = DWARF_DRD_BUFFER_VERSION;

	return (DW_DLV_OK);
}