#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ fde_initloc; scalar_t__ fde_adrange; TYPE_1__* fde_fs; int /*<<< orphan*/ * fde_dbg; } ;
struct TYPE_5__ {scalar_t__ fs_fdelen; } ;
typedef  scalar_t__ Dwarf_Unsigned ;
typedef  TYPE_1__* Dwarf_FrameSec ;
typedef  TYPE_2__* Dwarf_Fde ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  scalar_t__ Dwarf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int /*<<< orphan*/  DW_DLE_NO_ENTRY ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_fde_at_pc(Dwarf_Fde *fdelist, Dwarf_Addr pc, Dwarf_Fde *ret_fde,
    Dwarf_Addr *lopc, Dwarf_Addr *hipc, Dwarf_Error *error)
{
	Dwarf_FrameSec fs;
	Dwarf_Debug dbg;
	Dwarf_Fde fde;
	int i;

	dbg = fdelist != NULL ? (*fdelist)->fde_dbg : NULL;

	if (fdelist == NULL || ret_fde == NULL || lopc == NULL ||
	    hipc == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	fs = fdelist[0]->fde_fs;
	assert(fs != NULL);

	for (i = 0; (Dwarf_Unsigned)i < fs->fs_fdelen; i++) {
		fde = fdelist[i];
		if (pc >= fde->fde_initloc && pc < fde->fde_initloc +
		    fde->fde_adrange) {
			*ret_fde = fde;
			*lopc = fde->fde_initloc;
			*hipc = fde->fde_initloc + fde->fde_adrange - 1;
			return (DW_DLV_OK);
		}
	}

	DWARF_SET_ERROR(dbg, error, DW_DLE_NO_ENTRY);
	return (DW_DLV_NO_ENTRY);
}