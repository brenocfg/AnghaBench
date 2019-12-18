#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct readelf {scalar_t__ ec; int /*<<< orphan*/  dbg; } ;
struct TYPE_3__ {scalar_t__ dwr_type; scalar_t__ dwr_addr2; scalar_t__ dwr_addr1; } ;
typedef  scalar_t__ Dwarf_Unsigned ;
typedef  int Dwarf_Signed ;
typedef  TYPE_1__ Dwarf_Ranges ;
typedef  int /*<<< orphan*/  Dwarf_Off ;
typedef  scalar_t__ Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  int /*<<< orphan*/  Dwarf_Attribute ;
typedef  scalar_t__ Dwarf_Addr ;

/* Variables and functions */
 scalar_t__ DW_AT_ranges ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
 scalar_t__ DW_RANGES_ADDRESS_SELECTION ; 
 scalar_t__ DW_RANGES_END ; 
 scalar_t__ ELFCLASS32 ; 
 int dwarf_attrlist (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *) ; 
 int dwarf_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_errmsg (int /*<<< orphan*/ ) ; 
 int dwarf_formudata (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int dwarf_get_ranges (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**,int*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int dwarf_siblingof (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dwarf_whatattr (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_dwarf_ranges_foreach(struct readelf *re, Dwarf_Die die, Dwarf_Addr base)
{
	Dwarf_Attribute *attr_list;
	Dwarf_Ranges *ranges;
	Dwarf_Die ret_die;
	Dwarf_Error de;
	Dwarf_Addr base0;
	Dwarf_Half attr;
	Dwarf_Signed attr_count, cnt;
	Dwarf_Unsigned off, bytecnt;
	int i, j, ret;

	if ((ret = dwarf_attrlist(die, &attr_list, &attr_count, &de)) !=
	    DW_DLV_OK) {
		if (ret == DW_DLV_ERROR)
			warnx("dwarf_attrlist failed: %s", dwarf_errmsg(de));
		goto cont_search;
	}

	for (i = 0; i < attr_count; i++) {
		if (dwarf_whatattr(attr_list[i], &attr, &de) != DW_DLV_OK) {
			warnx("dwarf_whatattr failed: %s", dwarf_errmsg(de));
			continue;
		}
		if (attr != DW_AT_ranges)
			continue;
		if (dwarf_formudata(attr_list[i], &off, &de) != DW_DLV_OK) {
			warnx("dwarf_formudata failed: %s", dwarf_errmsg(de));
			continue;
		}
		if (dwarf_get_ranges(re->dbg, (Dwarf_Off) off, &ranges, &cnt,
		    &bytecnt, &de) != DW_DLV_OK)
			continue;
		base0 = base;
		for (j = 0; j < cnt; j++) {
			printf("    %08jx ", (uintmax_t) off);
			if (ranges[j].dwr_type == DW_RANGES_END) {
				printf("%s\n", "<End of list>");
				continue;
			} else if (ranges[j].dwr_type ==
			    DW_RANGES_ADDRESS_SELECTION) {
				base0 = ranges[j].dwr_addr2;
				continue;
			}
			if (re->ec == ELFCLASS32)
				printf("%08jx %08jx\n",
				    (uintmax_t) (ranges[j].dwr_addr1 + base0),
				    (uintmax_t) (ranges[j].dwr_addr2 + base0));
			else
				printf("%016jx %016jx\n",
				    (uintmax_t) (ranges[j].dwr_addr1 + base0),
				    (uintmax_t) (ranges[j].dwr_addr2 + base0));
		}
	}

cont_search:
	/* Search children. */
	ret = dwarf_child(die, &ret_die, &de);
	if (ret == DW_DLV_ERROR)
		warnx("dwarf_child: %s", dwarf_errmsg(de));
	else if (ret == DW_DLV_OK)
		dump_dwarf_ranges_foreach(re, ret_die, base);

	/* Search sibling. */
	ret = dwarf_siblingof(re->dbg, die, &ret_die, &de);
	if (ret == DW_DLV_ERROR)
		warnx("dwarf_siblingof: %s", dwarf_errmsg(de));
	else if (ret == DW_DLV_OK)
		dump_dwarf_ranges_foreach(re, ret_die, base);
}