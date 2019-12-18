#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct _Dwarf_Fde {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * fde_dbg; } ;
typedef  TYPE_1__* Dwarf_P_Fde ;
typedef  int /*<<< orphan*/ * Dwarf_P_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int /*<<< orphan*/  DW_DLE_MEMORY ; 
 TYPE_1__* DW_DLV_BADADDR ; 
 TYPE_1__* calloc (int,int) ; 

Dwarf_P_Fde
dwarf_new_fde(Dwarf_P_Debug dbg, Dwarf_Error *error)
{
	Dwarf_P_Fde fde;

	if (dbg == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_BADADDR);
	}

	if ((fde = calloc(1, sizeof(struct _Dwarf_Fde))) == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLV_BADADDR);
	}

	fde->fde_dbg = dbg;

	return (fde);
}