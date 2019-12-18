#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct _Dwarf_Arange {int dummy; } ;
struct TYPE_10__ {void* ar_eoff; scalar_t__ ar_esymndx; scalar_t__ ar_symndx; scalar_t__ ar_range; void* ar_address; TYPE_2__* ar_as; } ;
struct TYPE_9__ {int /*<<< orphan*/  as_arlist; } ;
struct TYPE_8__ {int dbgp_flags; TYPE_2__* dbgp_as; } ;
typedef  scalar_t__ Dwarf_Unsigned ;
typedef  TYPE_1__* Dwarf_P_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_2__* Dwarf_ArangeSet ;
typedef  TYPE_3__* Dwarf_Arange ;
typedef  void* Dwarf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int DW_DLC_SYMBOLIC_RELOCATIONS ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int /*<<< orphan*/  DW_DLE_MEMORY ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar_next ; 
 TYPE_3__* calloc (int,int) ; 

Dwarf_Unsigned
dwarf_add_arange_b(Dwarf_P_Debug dbg, Dwarf_Addr start, Dwarf_Unsigned length,
    Dwarf_Unsigned symbol_index, Dwarf_Unsigned end_symbol_index,
    Dwarf_Addr offset_from_end_symbol, Dwarf_Error *error)
{
	Dwarf_ArangeSet as;
	Dwarf_Arange ar;

	if (dbg == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (0);
	}
	as = dbg->dbgp_as;

	if (end_symbol_index > 0 &&
	    (dbg->dbgp_flags & DW_DLC_SYMBOLIC_RELOCATIONS) == 0) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (0);
	}

	if ((ar = calloc(1, sizeof(struct _Dwarf_Arange))) == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (0);
	}
	ar->ar_as = as;
	ar->ar_address = start;
	ar->ar_range = length;
	ar->ar_symndx = symbol_index;
	ar->ar_esymndx = end_symbol_index;
	ar->ar_eoff = offset_from_end_symbol;
	STAILQ_INSERT_TAIL(&as->as_arlist, ar, ar_next);

	return (1);
}