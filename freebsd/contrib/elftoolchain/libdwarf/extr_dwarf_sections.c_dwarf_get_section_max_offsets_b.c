#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dbg_seccnt; TYPE_1__* dbg_section; } ;
struct TYPE_4__ {char* ds_name; scalar_t__ ds_size; } ;
typedef  scalar_t__ Dwarf_Unsigned ;
typedef  TYPE_2__* Dwarf_Debug ;

/* Variables and functions */
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
 int /*<<< orphan*/  SET (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int
dwarf_get_section_max_offsets_b(Dwarf_Debug dbg, Dwarf_Unsigned *debug_info,
    Dwarf_Unsigned *debug_abbrev, Dwarf_Unsigned *debug_line,
    Dwarf_Unsigned *debug_loc, Dwarf_Unsigned *debug_aranges,
    Dwarf_Unsigned *debug_macinfo, Dwarf_Unsigned *debug_pubnames,
    Dwarf_Unsigned *debug_str, Dwarf_Unsigned *debug_frame,
    Dwarf_Unsigned *debug_ranges, Dwarf_Unsigned *debug_pubtypes,
    Dwarf_Unsigned *debug_types)
{
	const char *n;
	Dwarf_Unsigned sz;
	int i;

	if (dbg == NULL)
		return (DW_DLV_ERROR);

	SET(debug_info, 0);
	SET(debug_abbrev, 0);
	SET(debug_line, 0);
	SET(debug_loc, 0);
	SET(debug_aranges, 0);
	SET(debug_macinfo, 0);
	SET(debug_pubnames, 0);
	SET(debug_str, 0);
	SET(debug_frame, 0);
	SET(debug_ranges, 0);
	SET(debug_pubtypes, 0);
	SET(debug_types, 0);

	for (i = 0; (Dwarf_Unsigned) i < dbg->dbg_seccnt; i++) {
		n = dbg->dbg_section[i].ds_name;
		sz = dbg->dbg_section[i].ds_size;
		if (!strcmp(n, ".debug_info"))
			SET(debug_info, sz);
		else if (!strcmp(n, ".debug_abbrev"))
			SET(debug_abbrev, sz);
		else if (!strcmp(n, ".debug_line"))
			SET(debug_line, sz);
		else if (!strcmp(n, ".debug_loc"))
			SET(debug_loc, sz);
		else if (!strcmp(n, ".debug_aranges"))
			SET(debug_aranges, sz);
		else if (!strcmp(n, ".debug_macinfo"))
			SET(debug_macinfo, sz);
		else if (!strcmp(n, ".debug_pubnames"))
			SET(debug_pubnames, sz);
		else if (!strcmp(n, ".debug_str"))
			SET(debug_str, sz);
		else if (!strcmp(n, ".debug_frame"))
			SET(debug_frame, sz);
		else if (!strcmp(n, ".debug_ranges"))
			SET(debug_ranges, sz);
		else if (!strcmp(n, ".debug_pubtypes"))
			SET(debug_pubtypes, sz);
		else if (!strcmp(n, ".debug_types"))
			SET(debug_types, sz);
	}

	return (DW_DLV_OK);
}