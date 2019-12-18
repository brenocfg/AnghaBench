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
struct TYPE_8__ {scalar_t__ dbg_mode; char* dbg_strtab; scalar_t__ dbg_strtab_cap; scalar_t__ dbg_strtab_size; } ;
struct TYPE_7__ {scalar_t__ ds_data; scalar_t__ ds_size; } ;
typedef  TYPE_1__ Dwarf_Section ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_2__* Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ DW_DLC_RDWR ; 
 scalar_t__ DW_DLC_READ ; 
 int DW_DLE_MEMORY ; 
 int DW_DLE_NONE ; 
 scalar_t__ _INIT_DWARF_STRTAB_SIZE ; 
 TYPE_1__* _dwarf_find_section (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,scalar_t__) ; 

int
_dwarf_strtab_init(Dwarf_Debug dbg, Dwarf_Error *error)
{
	Dwarf_Section *ds;

	assert(dbg != NULL);

	if (dbg->dbg_mode == DW_DLC_READ || dbg->dbg_mode == DW_DLC_RDWR) {
		ds = _dwarf_find_section(dbg, ".debug_str");
		if (ds == NULL) {
			dbg->dbg_strtab = NULL;
			dbg->dbg_strtab_cap = dbg->dbg_strtab_size = 0;
			return (DW_DLE_NONE);
		}

		dbg->dbg_strtab_cap = dbg->dbg_strtab_size = ds->ds_size;

		if (dbg->dbg_mode == DW_DLC_RDWR) {
			if ((dbg->dbg_strtab = malloc((size_t) ds->ds_size)) ==
			    NULL) {
				DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
				return (DW_DLE_MEMORY);
			}
			memcpy(dbg->dbg_strtab, ds->ds_data, ds->ds_size);
		} else
			dbg->dbg_strtab = (char *) ds->ds_data;
	} else {
		/* DW_DLC_WRITE */

		dbg->dbg_strtab_cap = _INIT_DWARF_STRTAB_SIZE;
		dbg->dbg_strtab_size = 0;

		if ((dbg->dbg_strtab = malloc((size_t) dbg->dbg_strtab_cap)) ==
		    NULL) {
			DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
			return (DW_DLE_MEMORY);
		}

		dbg->dbg_strtab[0] = '\0';
	}

	return (DW_DLE_NONE);
}