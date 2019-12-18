#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  dbgp_drslist; void* dbgp_drspos; int /*<<< orphan*/  dbgp_seclist; void* dbgp_secpos; int /*<<< orphan*/  dbgp_vars; int /*<<< orphan*/  dbgp_types; int /*<<< orphan*/  dbgp_funcs; int /*<<< orphan*/  dbgp_weaks; int /*<<< orphan*/  dbgp_pubs; } ;
typedef  TYPE_1__* Dwarf_P_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int DW_DLE_NONE ; 
 void* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int _dwarf_abbrev_gen (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int _dwarf_arange_gen (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int _dwarf_frame_gen (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int _dwarf_info_gen (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int _dwarf_lineno_gen (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int _dwarf_macinfo_gen (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int _dwarf_nametbl_gen (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int _dwarf_reloc_gen (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int _dwarf_strtab_gen (TYPE_1__*,int /*<<< orphan*/ *) ; 

int
_dwarf_generate_sections(Dwarf_P_Debug dbg, Dwarf_Error *error)
{
	int ret;

	/* Produce .debug_info section. */
	if ((ret = _dwarf_info_gen(dbg, error)) != DW_DLE_NONE)
		return (ret);

	/* Produce .debug_abbrev section. */
	if ((ret = _dwarf_abbrev_gen(dbg, error)) != DW_DLE_NONE)
		return (ret);

	/* Produce .debug_line section. */
	if ((ret = _dwarf_lineno_gen(dbg, error)) != DW_DLE_NONE)
		return (ret);

	/* Produce .debug_frame section. */
	if ((ret = _dwarf_frame_gen(dbg, error)) != DW_DLE_NONE)
		return (ret);

	/* Produce .debug_aranges section. */
	if ((ret = _dwarf_arange_gen(dbg, error)) != DW_DLE_NONE)
		return (ret);

	/* Produce .debug_macinfo section. */
	if ((ret = _dwarf_macinfo_gen(dbg, error)) != DW_DLE_NONE)
		return (ret);

	/* Produce .debug_pubnames section. */
	if ((ret = _dwarf_nametbl_gen(dbg, ".debug_pubnames", dbg->dbgp_pubs,
	    error)) != DW_DLE_NONE)
		return (ret);

	/* Produce .debug_weaknames section. */
	if ((ret = _dwarf_nametbl_gen(dbg, ".debug_weaknames", dbg->dbgp_weaks,
	    error)) != DW_DLE_NONE)
		return (ret);

	/* Produce .debug_funcnames section. */
	if ((ret = _dwarf_nametbl_gen(dbg, ".debug_funcnames", dbg->dbgp_funcs,
	    error)) != DW_DLE_NONE)
		return (ret);

	/* Produce .debug_typenames section. */
	if ((ret = _dwarf_nametbl_gen(dbg, ".debug_typenames", dbg->dbgp_types,
	    error)) != DW_DLE_NONE)
		return (ret);

	/* Produce .debug_varnames section. */
	if ((ret = _dwarf_nametbl_gen(dbg, ".debug_varnames", dbg->dbgp_vars,
	    error)) != DW_DLE_NONE)
		return (ret);

	/* Produce .debug_str section. */
	if ((ret = _dwarf_strtab_gen(dbg, error)) != DW_DLE_NONE)
		return (ret);

	/* Finally, update and generate all relocation sections. */
	if ((ret = _dwarf_reloc_gen(dbg, error)) != DW_DLE_NONE)
		return (ret);

	/* Set section/relocation iterator to the first element. */
	dbg->dbgp_secpos = STAILQ_FIRST(&dbg->dbgp_seclist);
	dbg->dbgp_drspos = STAILQ_FIRST(&dbg->dbgp_drslist);
	
	return (DW_DLE_NONE);
}