#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_9__ {unsigned int cie_length; int cie_version; unsigned int cie_ra; scalar_t__ cie_offset; scalar_t__ cie_instlen; int /*<<< orphan*/ * cie_initinst; int /*<<< orphan*/  cie_daf; int /*<<< orphan*/  cie_caf; int /*<<< orphan*/ * cie_augment; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ ,scalar_t__*,unsigned int,int) ;int /*<<< orphan*/  dbg_pointer_size; } ;
struct TYPE_7__ {int /*<<< orphan*/  ds_data; scalar_t__ ds_size; } ;
typedef  scalar_t__ Dwarf_Unsigned ;
typedef  TYPE_1__* Dwarf_P_Section ;
typedef  TYPE_2__* Dwarf_P_Debug ;
typedef  TYPE_3__* Dwarf_P_Cie ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 unsigned int DW_CFA_nop ; 
 int DW_DLE_NONE ; 
 int /*<<< orphan*/  RCHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_BLOCK (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  WRITE_SLEB128 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ULEB128 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_VALUE (unsigned int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned int roundup (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__*,unsigned int,int) ; 

__attribute__((used)) static int
_dwarf_frame_gen_cie(Dwarf_P_Debug dbg, Dwarf_P_Section ds, Dwarf_P_Cie cie,
    Dwarf_Error *error)
{
	Dwarf_Unsigned len;
	uint64_t offset;
	int ret;

	assert(dbg != NULL && ds != NULL && cie != NULL);

	cie->cie_offset = offset = ds->ds_size;
	cie->cie_length = 0;
	cie->cie_version = 1;

	/* Length placeholder. */
	RCHECK(WRITE_VALUE(cie->cie_length, 4));

	/* .debug_frame use CIE id ~0. */
	RCHECK(WRITE_VALUE(~0U, 4));

	/* .debug_frame version is 1. (DWARF2) */
	RCHECK(WRITE_VALUE(cie->cie_version, 1));

	/* Write augmentation, if present. */
	if (cie->cie_augment != NULL)
		RCHECK(WRITE_BLOCK(cie->cie_augment,
		    strlen((char *) cie->cie_augment) + 1));
	else
		RCHECK(WRITE_VALUE(0, 1));

	/* Write caf, daf and ra. */
	RCHECK(WRITE_ULEB128(cie->cie_caf));
	RCHECK(WRITE_SLEB128(cie->cie_daf));
	RCHECK(WRITE_VALUE(cie->cie_ra, 1));

	/* Write initial instructions, if present. */
	if (cie->cie_initinst != NULL)
		RCHECK(WRITE_BLOCK(cie->cie_initinst, cie->cie_instlen));

	/* Add padding. */
	len = ds->ds_size - cie->cie_offset - 4;
	cie->cie_length = roundup(len, dbg->dbg_pointer_size);
	while (len++ < cie->cie_length)
		RCHECK(WRITE_VALUE(DW_CFA_nop, 1));

	/* Fill in the length field. */
	dbg->write(ds->ds_data, &offset, cie->cie_length, 4);
	
	return (DW_DLE_NONE);

gen_fail:
	return (ret);
}