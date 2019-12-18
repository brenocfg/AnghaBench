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
struct _Dwarf_Rel_Entry {int dummy; } ;
struct TYPE_14__ {int dbgp_flags; int (* write_alloc ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**,void*,unsigned char,int /*<<< orphan*/ *) ;} ;
struct TYPE_13__ {void* ds_size; int /*<<< orphan*/  ds_cap; int /*<<< orphan*/  ds_data; } ;
struct TYPE_12__ {unsigned char dre_length; int /*<<< orphan*/ * dre_secname; scalar_t__ dre_addend; void* dre_symndx; void* dre_offset; int /*<<< orphan*/  dre_type; } ;
struct TYPE_11__ {int drs_drecnt; int /*<<< orphan*/  drs_dre; } ;
typedef  void* Dwarf_Unsigned ;
typedef  TYPE_1__* Dwarf_Rel_Section ;
typedef  TYPE_2__* Dwarf_Rel_Entry ;
typedef  TYPE_3__* Dwarf_P_Section ;
typedef  TYPE_4__* Dwarf_P_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int DW_DLC_SYMBOLIC_RELOCATIONS ; 
 int DW_DLE_MEMORY ; 
 int DW_DLE_NONE ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  dre_next ; 
 int /*<<< orphan*/  dwarf_drt_first_of_length_pair ; 
 int /*<<< orphan*/  dwarf_drt_second_of_length_pair ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**,void*,unsigned char,int /*<<< orphan*/ *) ; 

int
_dwarf_reloc_entry_add_pair(Dwarf_P_Debug dbg, Dwarf_Rel_Section drs,
    Dwarf_P_Section ds, unsigned char length, Dwarf_Unsigned offset,
    Dwarf_Unsigned symndx, Dwarf_Unsigned esymndx, Dwarf_Unsigned symoff,
    Dwarf_Unsigned esymoff, Dwarf_Error *error)
{
	Dwarf_Rel_Entry dre;
	Dwarf_Unsigned reloff;
	int ret;

	assert(drs != NULL);
	assert(offset <= ds->ds_size);
	assert(dbg->dbgp_flags & DW_DLC_SYMBOLIC_RELOCATIONS);
	reloff = offset;

	/* Write net offset into section stream. */
	ret = dbg->write_alloc(&ds->ds_data, &ds->ds_cap, &offset,
	    esymoff - symoff, length, error);
	if (ret != DW_DLE_NONE)
		return (ret);
	if (offset > ds->ds_size)
		ds->ds_size = offset;

	if ((dre = calloc(2, sizeof(struct _Dwarf_Rel_Entry))) == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLE_MEMORY);
	}
	STAILQ_INSERT_TAIL(&drs->drs_dre, &dre[0], dre_next);
	STAILQ_INSERT_TAIL(&drs->drs_dre, &dre[1], dre_next);
	dre[0].dre_type = dwarf_drt_first_of_length_pair;
	dre[0].dre_length = length;
	dre[0].dre_offset = reloff;
	dre[0].dre_symndx = symndx;
	dre[0].dre_addend = 0;
	dre[0].dre_secname = NULL;
	dre[1].dre_type = dwarf_drt_second_of_length_pair;
	dre[1].dre_length = length;
	dre[1].dre_offset = reloff;
	dre[1].dre_symndx = esymndx;
	dre[1].dre_addend = 0;
	dre[1].dre_secname = NULL;
	drs->drs_drecnt += 2;

	return (DW_DLE_NONE);
}