#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct _Dwarf_Rel_Section {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_14__ {int dbgp_flags; int /*<<< orphan*/  dbgp_drscnt; int /*<<< orphan*/  dbgp_drslist; } ;
struct TYPE_13__ {int /*<<< orphan*/  ds_name; } ;
struct TYPE_12__ {int drs_addend; int /*<<< orphan*/  drs_dre; int /*<<< orphan*/  drs_ds; TYPE_2__* drs_ref; } ;
typedef  TYPE_1__* Dwarf_Rel_Section ;
typedef  TYPE_2__* Dwarf_P_Section ;
typedef  TYPE_3__* Dwarf_P_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int DW_DLC_SIZE_64 ; 
 int DW_DLC_SYMBOLIC_RELOCATIONS ; 
 int DW_DLE_MEMORY ; 
 scalar_t__ DW_DLE_NONE ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ _dwarf_section_init (TYPE_3__*,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  drs_next ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 

int
_dwarf_reloc_section_init(Dwarf_P_Debug dbg, Dwarf_Rel_Section *drsp,
    Dwarf_P_Section ref, Dwarf_Error *error)
{
	Dwarf_Rel_Section drs;
	char name[128];
	int pseudo;

	assert(dbg != NULL && drsp != NULL && ref != NULL);

	if ((drs = calloc(1, sizeof(struct _Dwarf_Rel_Section))) == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLE_MEMORY);
	}

	drs->drs_ref = ref;

	/*
	 * FIXME The logic here is most likely wrong. It should
	 * be the ISA that determines relocation type.
	 */
	if (dbg->dbgp_flags & DW_DLC_SIZE_64)
		drs->drs_addend = 1;
	else
		drs->drs_addend = 0;

	if (dbg->dbgp_flags & DW_DLC_SYMBOLIC_RELOCATIONS)
		pseudo = 1;
	else
		pseudo = 0;

	snprintf(name, sizeof(name), "%s%s",
	    drs->drs_addend ? ".rela" : ".rel", ref->ds_name);
	if (_dwarf_section_init(dbg, &drs->drs_ds, name, pseudo, error) !=
	    DW_DLE_NONE) {
		free(drs);
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLE_MEMORY);
	}

	STAILQ_INIT(&drs->drs_dre);
	STAILQ_INSERT_TAIL(&dbg->dbgp_drslist, drs, drs_next);
	dbg->dbgp_drscnt++;
	*drsp = drs;

	return (DW_DLE_NONE);
}