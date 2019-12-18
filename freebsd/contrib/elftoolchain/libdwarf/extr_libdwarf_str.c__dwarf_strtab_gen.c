#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ dbg_strtab_size; int /*<<< orphan*/  dbg_strtab; } ;
struct TYPE_11__ {scalar_t__ ds_cap; scalar_t__ ds_size; int /*<<< orphan*/ * ds_data; } ;
typedef  TYPE_1__* Dwarf_P_Section ;
typedef  TYPE_2__* Dwarf_P_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_MEMORY ; 
 int DW_DLE_NONE ; 
 int /*<<< orphan*/  SHT_PROGBITS ; 
 int _dwarf_section_callback (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _dwarf_section_free (TYPE_2__*,TYPE_1__**) ; 
 int _dwarf_section_init (TYPE_2__*,TYPE_1__**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,size_t) ; 

int
_dwarf_strtab_gen(Dwarf_P_Debug dbg, Dwarf_Error *error)
{
	Dwarf_P_Section ds;
	int ret;

	assert(dbg != NULL);

	if ((ret = _dwarf_section_init(dbg, &ds, ".debug_str", 0, error)) !=
	    DW_DLE_NONE)
		return (ret);

	if (dbg->dbg_strtab_size > ds->ds_cap) {
		ds->ds_data = realloc(ds->ds_data,
		    (size_t) dbg->dbg_strtab_size);
		if (ds->ds_data == NULL) {
			_dwarf_section_free(dbg, &ds);
			DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
			return (DW_DLE_MEMORY);
		}
		ds->ds_cap = dbg->dbg_strtab_size;
	}

	memcpy(ds->ds_data, dbg->dbg_strtab, dbg->dbg_strtab_size);
	ds->ds_size = dbg->dbg_strtab_size;

	/*
	 * Inform application the creation of .debug_str ELF section.
	 * Note that .debug_str use a different format than usual ELF
	 * string table, so it should not have SHT_STRTAB as its type.
	 */
	ret = _dwarf_section_callback(dbg, ds, SHT_PROGBITS, 0, 0, 0, error);

	return (ret);
}