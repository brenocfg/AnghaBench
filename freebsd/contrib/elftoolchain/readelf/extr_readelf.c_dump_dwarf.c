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
struct readelf {int dop; int /*<<< orphan*/  dbg; int /*<<< orphan*/  elf; } ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int DW_A ; 
 int /*<<< orphan*/  DW_DLC_READ ; 
 int DW_DLE_DEBUG_INFO_NULL ; 
 int DW_F ; 
 int DW_FF ; 
 int DW_I ; 
 int DW_L ; 
 int DW_LL ; 
 int DW_M ; 
 int DW_O ; 
 int DW_P ; 
 int DW_R ; 
 int DW_RR ; 
 int DW_S ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  dump_dwarf_abbrev (struct readelf*) ; 
 int /*<<< orphan*/  dump_dwarf_aranges (struct readelf*) ; 
 int /*<<< orphan*/  dump_dwarf_frame (struct readelf*,int) ; 
 int /*<<< orphan*/  dump_dwarf_info (struct readelf*,int) ; 
 int /*<<< orphan*/  dump_dwarf_line (struct readelf*) ; 
 int /*<<< orphan*/  dump_dwarf_line_decoded (struct readelf*) ; 
 int /*<<< orphan*/  dump_dwarf_loclist (struct readelf*) ; 
 int /*<<< orphan*/  dump_dwarf_macinfo (struct readelf*) ; 
 int /*<<< orphan*/  dump_dwarf_pubnames (struct readelf*) ; 
 int /*<<< orphan*/  dump_dwarf_ranges (struct readelf*) ; 
 int /*<<< orphan*/  dump_dwarf_str (struct readelf*) ; 
 scalar_t__ dwarf_elf_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_errmsg (int /*<<< orphan*/ ) ; 
 int dwarf_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_dwarf(struct readelf *re)
{
	Dwarf_Error de;
	int error;

	if (dwarf_elf_init(re->elf, DW_DLC_READ, NULL, NULL, &re->dbg, &de)) {
		if ((error = dwarf_errno(de)) != DW_DLE_DEBUG_INFO_NULL)
			errx(EXIT_FAILURE, "dwarf_elf_init failed: %s",
			    dwarf_errmsg(de));
		return;
	}

	if (re->dop & DW_A)
		dump_dwarf_abbrev(re);
	if (re->dop & DW_L)
		dump_dwarf_line(re);
	if (re->dop & DW_LL)
		dump_dwarf_line_decoded(re);
	if (re->dop & DW_I) {
		dump_dwarf_info(re, 0);
		dump_dwarf_info(re, 1);
	}
	if (re->dop & DW_P)
		dump_dwarf_pubnames(re);
	if (re->dop & DW_R)
		dump_dwarf_aranges(re);
	if (re->dop & DW_RR)
		dump_dwarf_ranges(re);
	if (re->dop & DW_M)
		dump_dwarf_macinfo(re);
	if (re->dop & DW_F)
		dump_dwarf_frame(re, 0);
	else if (re->dop & DW_FF)
		dump_dwarf_frame(re, 1);
	if (re->dop & DW_S)
		dump_dwarf_str(re);
	if (re->dop & DW_O)
		dump_dwarf_loclist(re);

	dwarf_finish(re->dbg, &de);
}