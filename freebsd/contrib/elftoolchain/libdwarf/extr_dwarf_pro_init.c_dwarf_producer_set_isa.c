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
typedef  enum Dwarf_ISA { ____Placeholder_Dwarf_ISA } Dwarf_ISA ;
struct TYPE_4__ {int dbgp_isa; } ;
typedef  TYPE_1__* Dwarf_P_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
 int DW_ISA_MAX ; 

int
dwarf_producer_set_isa(Dwarf_P_Debug dbg, enum Dwarf_ISA isa,
    Dwarf_Error *error)
{

	if (dbg == NULL || isa >= DW_ISA_MAX) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	dbg->dbgp_isa = isa;

	return (DW_DLV_OK);
}