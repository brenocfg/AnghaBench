#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;

/* Variables and functions */
 int dwarf_get_section_max_offsets_b (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
dwarf_get_section_max_offsets(Dwarf_Debug dbg, Dwarf_Unsigned *debug_info,
    Dwarf_Unsigned *debug_abbrev, Dwarf_Unsigned *debug_line,
    Dwarf_Unsigned *debug_loc, Dwarf_Unsigned *debug_aranges,
    Dwarf_Unsigned *debug_macinfo, Dwarf_Unsigned *debug_pubnames,
    Dwarf_Unsigned *debug_str, Dwarf_Unsigned *debug_frame,
    Dwarf_Unsigned *debug_ranges, Dwarf_Unsigned *debug_pubtypes)
{

	return (dwarf_get_section_max_offsets_b(dbg, debug_info, debug_abbrev,
	    debug_line, debug_loc, debug_aranges, debug_macinfo,
	    debug_pubnames, debug_str, debug_frame, debug_ranges,
	    debug_pubtypes, NULL));
}