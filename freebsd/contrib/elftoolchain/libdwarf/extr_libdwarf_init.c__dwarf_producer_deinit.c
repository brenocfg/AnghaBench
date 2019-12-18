#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ dbg_mode; int /*<<< orphan*/  dbgp_vars; int /*<<< orphan*/  dbgp_types; int /*<<< orphan*/  dbgp_funcs; int /*<<< orphan*/  dbgp_weaks; int /*<<< orphan*/  dbgp_pubs; } ;
typedef  TYPE_1__* Dwarf_P_Debug ;

/* Variables and functions */
 scalar_t__ DW_DLC_WRITE ; 
 int /*<<< orphan*/  _dwarf_arange_pro_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  _dwarf_die_pro_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  _dwarf_expr_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  _dwarf_frame_pro_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  _dwarf_info_pro_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  _dwarf_lineno_pro_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  _dwarf_macinfo_pro_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  _dwarf_nametbl_pro_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _dwarf_reloc_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  _dwarf_section_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  _dwarf_strtab_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
_dwarf_producer_deinit(Dwarf_P_Debug dbg)
{

	assert(dbg != NULL && dbg->dbg_mode == DW_DLC_WRITE);

	_dwarf_info_pro_cleanup(dbg);
	_dwarf_die_pro_cleanup(dbg);
	_dwarf_expr_cleanup(dbg);
	_dwarf_lineno_pro_cleanup(dbg);
	_dwarf_frame_pro_cleanup(dbg);
	_dwarf_arange_pro_cleanup(dbg);
	_dwarf_macinfo_pro_cleanup(dbg);
	_dwarf_strtab_cleanup(dbg);
	_dwarf_nametbl_pro_cleanup(&dbg->dbgp_pubs);
	_dwarf_nametbl_pro_cleanup(&dbg->dbgp_weaks);
	_dwarf_nametbl_pro_cleanup(&dbg->dbgp_funcs);
	_dwarf_nametbl_pro_cleanup(&dbg->dbgp_types);
	_dwarf_nametbl_pro_cleanup(&dbg->dbgp_vars);
	_dwarf_section_cleanup(dbg);
	_dwarf_reloc_cleanup(dbg);
}