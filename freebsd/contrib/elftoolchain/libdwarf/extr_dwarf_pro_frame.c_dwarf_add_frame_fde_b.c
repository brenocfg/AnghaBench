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
struct TYPE_8__ {int dbgp_flags; int /*<<< orphan*/  dbgp_fdelen; int /*<<< orphan*/  dbgp_fdelist; int /*<<< orphan*/  dbgp_cielist; } ;
struct TYPE_7__ {void* fde_eoff; scalar_t__ fde_esymndx; scalar_t__ fde_symndx; scalar_t__ fde_adrange; void* fde_initloc; int /*<<< orphan*/ * fde_cie; TYPE_2__* fde_dbg; } ;
typedef  scalar_t__ Dwarf_Unsigned ;
typedef  TYPE_1__* Dwarf_P_Fde ;
typedef  int /*<<< orphan*/  Dwarf_P_Die ;
typedef  TYPE_2__* Dwarf_P_Debug ;
typedef  int /*<<< orphan*/ * Dwarf_P_Cie ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  void* Dwarf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int DW_DLC_SYMBOLIC_RELOCATIONS ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 scalar_t__ DW_DLV_NOCOUNT ; 
 int /*<<< orphan*/ * STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * STAILQ_NEXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cie_next ; 
 int /*<<< orphan*/  fde_next ; 

Dwarf_Unsigned
dwarf_add_frame_fde_b(Dwarf_P_Debug dbg, Dwarf_P_Fde fde, Dwarf_P_Die die,
    Dwarf_Unsigned cie, Dwarf_Addr virt_addr, Dwarf_Unsigned code_len,
    Dwarf_Unsigned symbol_index, Dwarf_Unsigned end_symbol_index,
    Dwarf_Addr offset_from_end_sym, Dwarf_Error *error)
{
	Dwarf_P_Cie ciep;
	int i;

	/*
	 * XXX SGI libdwarf need the DIE arg because later it will insert a
	 * DW_AT_MIPS_fde attribute, which points to the offset the
	 * correspoding FDE, into this DIE. Do we need this?
	 */
	(void) die;

	if (dbg == NULL || fde == NULL || fde->fde_dbg != dbg) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_NOCOUNT);
	}

	ciep = STAILQ_FIRST(&dbg->dbgp_cielist);
	for (i = 0; (Dwarf_Unsigned) i < cie; i++) {
		ciep = STAILQ_NEXT(ciep, cie_next);
		if (ciep == NULL)
			break;
	}
	if (ciep == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_NOCOUNT);
	}

	if (end_symbol_index > 0 &&
	    (dbg->dbgp_flags & DW_DLC_SYMBOLIC_RELOCATIONS) == 0) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_NOCOUNT);
	}

	fde->fde_cie = ciep;
	fde->fde_initloc = virt_addr;
	fde->fde_adrange = code_len;
	fde->fde_symndx = symbol_index;
	fde->fde_esymndx = end_symbol_index;
	fde->fde_eoff = offset_from_end_sym;

	STAILQ_INSERT_TAIL(&dbg->dbgp_fdelist, fde, fde_next);

	return (dbg->dbgp_fdelen++);
}