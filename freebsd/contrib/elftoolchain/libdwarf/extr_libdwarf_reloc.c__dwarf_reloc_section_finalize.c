#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int dbgp_flags; } ;
struct TYPE_13__ {scalar_t__ ds_size; int ds_cap; int ds_ndx; int /*<<< orphan*/  ds_symndx; int /*<<< orphan*/  ds_name; int /*<<< orphan*/ * ds_data; } ;
struct TYPE_12__ {int drs_drecnt; TYPE_1__* drs_ref; scalar_t__ drs_addend; TYPE_3__* drs_ds; } ;
struct TYPE_11__ {int /*<<< orphan*/  ds_ndx; } ;
typedef  int /*<<< orphan*/  Elf64_Rela ;
typedef  int /*<<< orphan*/  Elf64_Rel ;
typedef  int /*<<< orphan*/  Elf32_Rela ;
typedef  int /*<<< orphan*/  Elf32_Rel ;
typedef  int Dwarf_Unsigned ;
typedef  TYPE_2__* Dwarf_Rel_Section ;
typedef  TYPE_3__* Dwarf_P_Section ;
typedef  TYPE_4__* Dwarf_P_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int DW_DLC_SIZE_64 ; 
 int DW_DLC_SYMBOLIC_RELOCATIONS ; 
 int DW_DLE_ELF_SECT_ERR ; 
 int DW_DLE_MEMORY ; 
 int DW_DLE_NONE ; 
 int /*<<< orphan*/  SHT_REL ; 
 int /*<<< orphan*/  SHT_RELA ; 
 int _dwarf_pro_callback (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _dwarf_reloc_section_free (TYPE_4__*,TYPE_2__**) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,size_t) ; 

int
_dwarf_reloc_section_finalize(Dwarf_P_Debug dbg, Dwarf_Rel_Section drs,
    Dwarf_Error *error)
{
	Dwarf_P_Section ds;
	Dwarf_Unsigned unit;
	int ret, size;

	assert(dbg != NULL && drs != NULL && drs->drs_ds != NULL &&
	    drs->drs_ref != NULL);

	ds = drs->drs_ds;

	/*
	 * Calculate the size (in bytes) of the relocation section.
	 */
	if (dbg->dbgp_flags & DW_DLC_SIZE_64)
		unit = drs->drs_addend ? sizeof(Elf64_Rela) : sizeof(Elf64_Rel);
	else
		unit = drs->drs_addend ? sizeof(Elf32_Rela) : sizeof(Elf32_Rel);
	assert(ds->ds_size == 0);
	size = drs->drs_drecnt * unit;

	/*
	 * Discard this relocation section if there is no entry in it.
	 */
	if (size == 0) {
		_dwarf_reloc_section_free(dbg, &drs);
		return (DW_DLE_NONE);
	}

	/*
	 * If we are under stream mode, realloc the section data block to
	 * this size.
	 */
	if ((dbg->dbgp_flags & DW_DLC_SYMBOLIC_RELOCATIONS) == 0) {
		ds->ds_cap = size;
		if ((ds->ds_data = realloc(ds->ds_data, (size_t) ds->ds_cap)) ==
		    NULL) {
			DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
			return (DW_DLE_MEMORY);
		}
	}

	/*
	 * Notify the application the creation of this relocation section.
	 * Note that the section link here should point to the .symtab
	 * section, we set it to 0 since we have no way to know .symtab
	 * section index.
	 */
	ret = _dwarf_pro_callback(dbg, ds->ds_name, size,
	    drs->drs_addend ? SHT_RELA : SHT_REL, 0, 0, drs->drs_ref->ds_ndx,
	    &ds->ds_symndx, NULL);
	if (ret < 0) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ELF_SECT_ERR);
		return (DW_DLE_ELF_SECT_ERR);
	}
	ds->ds_ndx = ret;

	return (DW_DLE_NONE);
}