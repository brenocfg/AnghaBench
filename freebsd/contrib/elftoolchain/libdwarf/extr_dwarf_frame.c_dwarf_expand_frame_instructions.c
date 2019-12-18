#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cie_addrsize; int /*<<< orphan*/ * cie_dbg; } ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  int /*<<< orphan*/  Dwarf_Signed ;
typedef  int /*<<< orphan*/ * Dwarf_Ptr ;
typedef  int /*<<< orphan*/  Dwarf_Frame_Op ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  TYPE_1__* Dwarf_Cie ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int DW_DLE_NONE ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
 int _dwarf_frame_get_fop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
dwarf_expand_frame_instructions(Dwarf_Cie cie, Dwarf_Ptr instruction,
    Dwarf_Unsigned len, Dwarf_Frame_Op **ret_oplist, Dwarf_Signed *ret_opcnt,
    Dwarf_Error *error)
{
	Dwarf_Debug dbg;
	int ret;

	dbg = cie != NULL ? cie->cie_dbg : NULL;

	if (cie == NULL || instruction == NULL || len == 0 ||
	    ret_oplist == NULL || ret_opcnt == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	ret = _dwarf_frame_get_fop(dbg, cie->cie_addrsize, instruction, len,
	    ret_oplist, ret_opcnt, error);
	if (ret != DW_DLE_NONE)
		return (DW_DLV_ERROR);

	return (DW_DLV_OK);
}