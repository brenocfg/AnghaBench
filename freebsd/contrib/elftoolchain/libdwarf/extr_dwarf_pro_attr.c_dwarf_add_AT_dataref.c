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
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  int /*<<< orphan*/ * Dwarf_P_Die ;
typedef  int /*<<< orphan*/ * Dwarf_P_Debug ;
typedef  int /*<<< orphan*/  Dwarf_P_Attribute ;
typedef  int /*<<< orphan*/  Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/  Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int DW_DLE_NONE ; 
 int /*<<< orphan*/  DW_DLV_BADADDR ; 
 int _dwarf_add_AT_dataref (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

Dwarf_P_Attribute
dwarf_add_AT_dataref(Dwarf_P_Debug dbg, Dwarf_P_Die die, Dwarf_Half attr,
    Dwarf_Unsigned pc_value, Dwarf_Unsigned sym_index, Dwarf_Error *error)
{
	Dwarf_Attribute at;
	int ret;

	if (dbg == NULL || die == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_BADADDR);
	}

	ret = _dwarf_add_AT_dataref(dbg, die, attr, pc_value, sym_index,
	    NULL, &at, error);
	if (ret != DW_DLE_NONE)
		return (DW_DLV_BADADDR);

	return (at);

}