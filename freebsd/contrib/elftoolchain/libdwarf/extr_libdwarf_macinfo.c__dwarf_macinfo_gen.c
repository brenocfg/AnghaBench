#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int dmd_type; int /*<<< orphan*/  dmd_fileindex; int /*<<< orphan*/  dmd_lineno; int /*<<< orphan*/ * dmd_macro; int /*<<< orphan*/  dmd_offset; } ;
struct TYPE_12__ {scalar_t__ dbgp_mdcnt; TYPE_3__* dbgp_mdlist; } ;
struct TYPE_11__ {int /*<<< orphan*/  ds_size; } ;
typedef  scalar_t__ Dwarf_Unsigned ;
typedef  TYPE_1__* Dwarf_P_Section ;
typedef  TYPE_2__* Dwarf_P_Debug ;
typedef  TYPE_3__ Dwarf_Macro_Details ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int DW_DLE_NONE ; 
#define  DW_MACINFO_define 132 
#define  DW_MACINFO_end_file 131 
#define  DW_MACINFO_start_file 130 
#define  DW_MACINFO_undef 129 
#define  DW_MACINFO_vendor_ext 128 
 int /*<<< orphan*/  RCHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHT_PROGBITS ; 
 int /*<<< orphan*/  WRITE_STRING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WRITE_ULEB128 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_VALUE (int,int) ; 
 int /*<<< orphan*/  _dwarf_section_callback (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _dwarf_section_free (TYPE_2__*,TYPE_1__**) ; 
 int /*<<< orphan*/  _dwarf_section_init (TYPE_2__*,TYPE_1__**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
_dwarf_macinfo_gen(Dwarf_P_Debug dbg, Dwarf_Error *error)
{
	Dwarf_P_Section ds;
	Dwarf_Macro_Details *md;
	int i, ret;

	if (dbg->dbgp_mdcnt == 0)
		return (DW_DLE_NONE);

	/* Create .debug_frame section. */
	RCHECK(_dwarf_section_init(dbg, &ds, ".debug_macinfo", 0, error));

	/* Write the list of Dwarf_Macro_Details. */
	for (i = 0; (Dwarf_Unsigned) i < dbg->dbgp_mdcnt; i++) {
		md = &dbg->dbgp_mdlist[i];
		md->dmd_offset = ds->ds_size;
		RCHECK(WRITE_VALUE(md->dmd_type, 1));
		switch (md->dmd_type) {
		case DW_MACINFO_define:
		case DW_MACINFO_undef:
		case DW_MACINFO_vendor_ext:
			RCHECK(WRITE_ULEB128(md->dmd_lineno));
			assert(md->dmd_macro != NULL);
			RCHECK(WRITE_STRING(md->dmd_macro));
			break;
		case DW_MACINFO_start_file:
			RCHECK(WRITE_ULEB128(md->dmd_lineno));
			RCHECK(WRITE_ULEB128(md->dmd_fileindex));
			break;
		case DW_MACINFO_end_file:
			break;
		default:
			assert(0);
			break;
		}
	}
	RCHECK(WRITE_VALUE(0, 1));

	/* Inform application the creation of .debug_macinfo ELF section. */
	RCHECK(_dwarf_section_callback(dbg, ds, SHT_PROGBITS, 0, 0, 0, error));

	return (DW_DLE_NONE);

gen_fail:
	_dwarf_section_free(dbg, &ds);

	return (ret);
}