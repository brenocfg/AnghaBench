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
struct TYPE_3__ {int /*<<< orphan*/  fde_instlen; int /*<<< orphan*/  fde_inst; int /*<<< orphan*/ * fde_dbg; } ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  int /*<<< orphan*/  Dwarf_Ptr ;
typedef  TYPE_1__* Dwarf_Fde ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 

int
dwarf_get_fde_instr_bytes(Dwarf_Fde fde, Dwarf_Ptr *ret_inst,
    Dwarf_Unsigned *ret_len, Dwarf_Error *error)
{
	Dwarf_Debug dbg;

	dbg = fde != NULL ? fde->fde_dbg : NULL;

	if (fde == NULL || ret_inst == NULL || ret_len == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	*ret_inst = fde->fde_inst;
	*ret_len = fde->fde_instlen;

	return (DW_DLV_OK);
}