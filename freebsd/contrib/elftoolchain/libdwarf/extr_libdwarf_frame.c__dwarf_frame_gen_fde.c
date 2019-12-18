#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_15__ {int dbg_pointer_size; int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_14__ {scalar_t__ fde_esymndx; int /*<<< orphan*/  fde_length; scalar_t__ fde_offset; int /*<<< orphan*/  fde_instlen; int /*<<< orphan*/  fde_inst; int /*<<< orphan*/  fde_adrange; int /*<<< orphan*/  fde_eoff; int /*<<< orphan*/  fde_initloc; int /*<<< orphan*/  fde_symndx; int /*<<< orphan*/  fde_cieoff; TYPE_1__* fde_cie; } ;
struct TYPE_13__ {int /*<<< orphan*/  ds_data; scalar_t__ ds_size; } ;
struct TYPE_12__ {int /*<<< orphan*/  cie_offset; } ;
typedef  scalar_t__ Dwarf_Unsigned ;
typedef  int /*<<< orphan*/ * Dwarf_Rel_Section ;
typedef  TYPE_2__* Dwarf_P_Section ;
typedef  TYPE_3__* Dwarf_P_Fde ;
typedef  TYPE_4__* Dwarf_P_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DW_CFA_nop ; 
 int DW_DLE_NONE ; 
 int /*<<< orphan*/  RCHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_BLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_VALUE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _dwarf_reloc_entry_add (TYPE_4__*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _dwarf_reloc_entry_add_pair (TYPE_4__*,int /*<<< orphan*/ *,TYPE_2__*,int,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dwarf_drt_data_reloc ; 
 int /*<<< orphan*/  roundup (scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
_dwarf_frame_gen_fde(Dwarf_P_Debug dbg, Dwarf_P_Section ds,
    Dwarf_Rel_Section drs, Dwarf_P_Fde fde, Dwarf_Error *error)
{
	Dwarf_Unsigned len;
	uint64_t offset;
	int ret;

	assert(dbg != NULL && ds != NULL && drs != NULL);
	assert(fde != NULL && fde->fde_cie != NULL);

	fde->fde_offset = offset = ds->ds_size;
	fde->fde_length = 0;
	fde->fde_cieoff = fde->fde_cie->cie_offset;

	/* Length placeholder. */
	RCHECK(WRITE_VALUE(fde->fde_length, 4));

	/* Write CIE pointer. */
	RCHECK(_dwarf_reloc_entry_add(dbg, drs, ds, dwarf_drt_data_reloc, 4,
	    ds->ds_size, 0, fde->fde_cieoff, ".debug_frame", error));

	/* Write FDE initial location. */
	RCHECK(_dwarf_reloc_entry_add(dbg, drs, ds, dwarf_drt_data_reloc,
	    dbg->dbg_pointer_size, ds->ds_size, fde->fde_symndx,
	    fde->fde_initloc, NULL, error));

	/*
	 * Write FDE address range. Use a pair of relocation entries if
	 * application provided end symbol index. Otherwise write the
	 * length without assoicating any relocation info.
	 */
	if (fde->fde_esymndx > 0)
		RCHECK(_dwarf_reloc_entry_add_pair(dbg, drs, ds,
		    dbg->dbg_pointer_size, ds->ds_size, fde->fde_symndx,
		    fde->fde_esymndx, fde->fde_initloc, fde->fde_eoff, error));
	else
		RCHECK(WRITE_VALUE(fde->fde_adrange, dbg->dbg_pointer_size));

	/* Write FDE frame instructions. */
	RCHECK(WRITE_BLOCK(fde->fde_inst, fde->fde_instlen));

	/* Add padding. */
	len = ds->ds_size - fde->fde_offset - 4;
	fde->fde_length = roundup(len, dbg->dbg_pointer_size);
	while (len++ < fde->fde_length)
		RCHECK(WRITE_VALUE(DW_CFA_nop, 1));

	/* Fill in the length field. */
	dbg->write(ds->ds_data, &offset, fde->fde_length, 4);

	return (DW_DLE_NONE);

gen_fail:
	return (ret);
}