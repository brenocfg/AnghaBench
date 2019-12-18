#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * ds_data; int /*<<< orphan*/  ds_size; int /*<<< orphan*/  ds_ndx; } ;
struct TYPE_6__ {TYPE_3__* dbgp_secpos; } ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  int /*<<< orphan*/  Dwarf_Signed ;
typedef  int /*<<< orphan*/ * Dwarf_Ptr ;
typedef  TYPE_1__* Dwarf_P_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int /*<<< orphan*/  DW_DLE_NO_ENTRY ; 
 TYPE_3__* STAILQ_NEXT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds_next ; 

Dwarf_Ptr
dwarf_get_section_bytes(Dwarf_P_Debug dbg, Dwarf_Signed dwarf_section,
    Dwarf_Signed *elf_section_index, Dwarf_Unsigned *length, Dwarf_Error *error)
{
	Dwarf_Ptr data;

	(void) dwarf_section;	/* ignored. */

	if (dbg == NULL || elf_section_index == NULL || length == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (NULL);
	}

	if (dbg->dbgp_secpos == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_NO_ENTRY);
		return (NULL);
	}

	*elf_section_index = dbg->dbgp_secpos->ds_ndx;
	*length = dbg->dbgp_secpos->ds_size;
	data = dbg->dbgp_secpos->ds_data;

	dbg->dbgp_secpos = STAILQ_NEXT(dbg->dbgp_secpos, ds_next);

	return (data);
}