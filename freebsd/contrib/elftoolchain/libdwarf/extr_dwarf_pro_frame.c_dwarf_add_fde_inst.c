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
typedef  int /*<<< orphan*/  Dwarf_Small ;
typedef  int /*<<< orphan*/ * Dwarf_P_Fde ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int DW_DLE_NONE ; 
 int /*<<< orphan*/ * DW_DLV_BADADDR ; 
 int _dwarf_frame_fde_add_inst (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

Dwarf_P_Fde
dwarf_add_fde_inst(Dwarf_P_Fde fde, Dwarf_Small op, Dwarf_Unsigned val1,
    Dwarf_Unsigned val2, Dwarf_Error *error)
{
	int ret;

	if (fde == NULL) {
		DWARF_SET_ERROR(NULL, error, DW_DLE_ARGUMENT);
		return (DW_DLV_BADADDR);
	}

	ret = _dwarf_frame_fde_add_inst(fde, op, val1, val2, error);

	if (ret != DW_DLE_NONE)
		return (DW_DLV_BADADDR);

	return (fde);
}