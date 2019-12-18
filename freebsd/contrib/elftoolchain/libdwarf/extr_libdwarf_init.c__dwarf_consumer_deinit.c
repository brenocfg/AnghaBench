#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ dbg_mode; int /*<<< orphan*/  dbg_section; int /*<<< orphan*/  dbg_types; int /*<<< orphan*/  dbg_vars; int /*<<< orphan*/  dbg_funcs; int /*<<< orphan*/  dbg_weaks; int /*<<< orphan*/  dbg_pubtypes; int /*<<< orphan*/  dbg_globals; } ;
typedef  TYPE_1__* Dwarf_Debug ;

/* Variables and functions */
 scalar_t__ DW_DLC_READ ; 
 int /*<<< orphan*/  _dwarf_arange_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  _dwarf_frame_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  _dwarf_info_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  _dwarf_macinfo_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  _dwarf_nametbl_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _dwarf_ranges_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  _dwarf_strtab_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_dwarf_consumer_deinit(Dwarf_Debug dbg)
{

	assert(dbg != NULL && dbg->dbg_mode == DW_DLC_READ);

	_dwarf_info_cleanup(dbg);
	_dwarf_ranges_cleanup(dbg);
	_dwarf_frame_cleanup(dbg);
	_dwarf_arange_cleanup(dbg);
	_dwarf_macinfo_cleanup(dbg);
	_dwarf_strtab_cleanup(dbg);
	_dwarf_nametbl_cleanup(&dbg->dbg_globals);
	_dwarf_nametbl_cleanup(&dbg->dbg_pubtypes);
	_dwarf_nametbl_cleanup(&dbg->dbg_weaks);
	_dwarf_nametbl_cleanup(&dbg->dbg_funcs);
	_dwarf_nametbl_cleanup(&dbg->dbg_vars);
	_dwarf_nametbl_cleanup(&dbg->dbg_types);

	free(dbg->dbg_section);
}