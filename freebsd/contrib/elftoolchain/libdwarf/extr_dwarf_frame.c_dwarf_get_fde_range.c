#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  fde_offset; TYPE_1__* fde_cie; int /*<<< orphan*/  fde_cieoff; int /*<<< orphan*/  fde_length; int /*<<< orphan*/  fde_addr; int /*<<< orphan*/  fde_adrange; int /*<<< orphan*/  fde_initloc; int /*<<< orphan*/ * fde_dbg; } ;
struct TYPE_4__ {int /*<<< orphan*/  cie_index; } ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  int /*<<< orphan*/  Dwarf_Signed ;
typedef  int /*<<< orphan*/  Dwarf_Ptr ;
typedef  int /*<<< orphan*/  Dwarf_Off ;
typedef  TYPE_2__* Dwarf_Fde ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 

int
dwarf_get_fde_range(Dwarf_Fde fde, Dwarf_Addr *low_pc, Dwarf_Unsigned *func_len,
    Dwarf_Ptr *fde_bytes, Dwarf_Unsigned *fde_byte_len, Dwarf_Off *cie_offset,
    Dwarf_Signed *cie_index, Dwarf_Off *fde_offset, Dwarf_Error *error)
{
	Dwarf_Debug dbg;

	dbg = fde != NULL ? fde->fde_dbg : NULL;

	if (fde == NULL || low_pc == NULL || func_len == NULL ||
	    fde_bytes == NULL || fde_byte_len == NULL || cie_offset == NULL ||
	    cie_index == NULL || fde_offset == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	*low_pc = fde->fde_initloc;
	*func_len = fde->fde_adrange;
	*fde_bytes = fde->fde_addr;
	*fde_byte_len = fde->fde_length;
	*cie_offset = fde->fde_cieoff;
	*cie_index = fde->fde_cie->cie_index;
	*fde_offset = fde->fde_offset;

	return (DW_DLV_OK);
}