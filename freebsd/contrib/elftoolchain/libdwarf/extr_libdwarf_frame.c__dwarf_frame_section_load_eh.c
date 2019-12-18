#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dbg_eh_frame; } ;
typedef  int /*<<< orphan*/  Dwarf_Section ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_1__* Dwarf_Debug ;

/* Variables and functions */
 int DW_DLE_NONE ; 
 int /*<<< orphan*/ * _dwarf_find_section (TYPE_1__*,char*) ; 
 int _dwarf_frame_section_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int
_dwarf_frame_section_load_eh(Dwarf_Debug dbg, Dwarf_Error *error)
{
	Dwarf_Section *ds;

	if ((ds = _dwarf_find_section(dbg, ".eh_frame")) != NULL) {
		return (_dwarf_frame_section_init(dbg, &dbg->dbg_eh_frame,
		    ds, 1, error));
	}

	return (DW_DLE_NONE);
}