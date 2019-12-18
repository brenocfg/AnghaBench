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
struct readelf {scalar_t__ ec; int /*<<< orphan*/  dbg; } ;
typedef  scalar_t__ Dwarf_Unsigned ;
typedef  int /*<<< orphan*/  Dwarf_Signed ;
typedef  int /*<<< orphan*/  Dwarf_Ranges ;
typedef  scalar_t__ Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Die ;
typedef  int /*<<< orphan*/  Dwarf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_low_pc ; 
 int DW_DLV_OK ; 
 scalar_t__ DW_TAG_compile_unit ; 
 scalar_t__ ELFCLASS32 ; 
 int /*<<< orphan*/  dump_dwarf_ranges_foreach (struct readelf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dwarf_attrval_unsigned (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_errmsg (int /*<<< orphan*/ ) ; 
 int dwarf_get_ranges (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int dwarf_next_cu_header (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dwarf_siblingof (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int dwarf_tag (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_dwarf_ranges(struct readelf *re)
{
	Dwarf_Ranges *ranges;
	Dwarf_Die die;
	Dwarf_Signed cnt;
	Dwarf_Unsigned bytecnt;
	Dwarf_Half tag;
	Dwarf_Error de;
	Dwarf_Unsigned lowpc;
	int ret;

	if (dwarf_get_ranges(re->dbg, 0, &ranges, &cnt, &bytecnt, &de) !=
	    DW_DLV_OK)
		return;

	printf("Contents of the .debug_ranges section:\n\n");
	if (re->ec == ELFCLASS32)
		printf("    %-8s %-8s %s\n", "Offset", "Begin", "End");
	else
		printf("    %-8s %-16s %s\n", "Offset", "Begin", "End");

	while ((ret = dwarf_next_cu_header(re->dbg, NULL, NULL, NULL, NULL,
	    NULL, &de)) == DW_DLV_OK) {
		die = NULL;
		if (dwarf_siblingof(re->dbg, die, &die, &de) != DW_DLV_OK)
			continue;
		if (dwarf_tag(die, &tag, &de) != DW_DLV_OK) {
			warnx("dwarf_tag failed: %s", dwarf_errmsg(de));
			continue;
		}
		/* XXX: What about DW_TAG_partial_unit? */
		lowpc = 0;
		if (tag == DW_TAG_compile_unit) {
			if (dwarf_attrval_unsigned(die, DW_AT_low_pc, &lowpc,
			    &de) != DW_DLV_OK)
				lowpc = 0;
		}

		dump_dwarf_ranges_foreach(re, die, (Dwarf_Addr) lowpc);
	}
	putchar('\n');
}