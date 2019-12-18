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
typedef  int /*<<< orphan*/  unk_tag ;
typedef  int /*<<< orphan*/  unk_form ;
typedef  int /*<<< orphan*/  unk_attr ;
struct readelf {int /*<<< orphan*/  dbg; } ;
typedef  int Dwarf_Unsigned ;
typedef  scalar_t__ Dwarf_Signed ;
typedef  int Dwarf_Off ;
typedef  int Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/  Dwarf_Abbrev ;

/* Variables and functions */
 int /*<<< orphan*/  DW_DLA_ABBREV ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
 int /*<<< orphan*/  dwarf_dealloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf_errmsg (int /*<<< orphan*/ ) ; 
 int dwarf_get_AT_name (int,char const**) ; 
 int dwarf_get_FORM_name (scalar_t__,char const**) ; 
 int dwarf_get_TAG_name (int,char const**) ; 
 int dwarf_get_abbrev (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *) ; 
 int dwarf_get_abbrev_children_flag (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int dwarf_get_abbrev_entry (int /*<<< orphan*/ ,scalar_t__,int*,scalar_t__*,int*,int /*<<< orphan*/ *) ; 
 int dwarf_get_abbrev_tag (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int dwarf_next_cu_header (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_dwarf_abbrev(struct readelf *re)
{
	Dwarf_Abbrev ab;
	Dwarf_Off aboff, atoff;
	Dwarf_Unsigned length, attr_count;
	Dwarf_Signed flag, form;
	Dwarf_Half tag, attr;
	Dwarf_Error de;
	const char *tag_str, *attr_str, *form_str;
	char unk_tag[32], unk_attr[32], unk_form[32];
	int i, j, ret;

	printf("\nContents of section .debug_abbrev:\n\n");

	while ((ret = dwarf_next_cu_header(re->dbg, NULL, NULL, &aboff,
	    NULL, NULL, &de)) ==  DW_DLV_OK) {
		printf("  Number TAG\n");
		i = 0;
		while ((ret = dwarf_get_abbrev(re->dbg, aboff, &ab, &length,
		    &attr_count, &de)) == DW_DLV_OK) {
			if (length == 1) {
				dwarf_dealloc(re->dbg, ab, DW_DLA_ABBREV);
				break;
			}
			aboff += length;
			printf("%4d", ++i);
			if (dwarf_get_abbrev_tag(ab, &tag, &de) != DW_DLV_OK) {
				warnx("dwarf_get_abbrev_tag failed: %s",
				    dwarf_errmsg(de));
				goto next_abbrev;
			}
			if (dwarf_get_TAG_name(tag, &tag_str) != DW_DLV_OK) {
				snprintf(unk_tag, sizeof(unk_tag),
				    "[Unknown Tag: %#x]", tag);
				tag_str = unk_tag;
			}
			if (dwarf_get_abbrev_children_flag(ab, &flag, &de) !=
			    DW_DLV_OK) {
				warnx("dwarf_get_abbrev_children_flag failed:"
				    " %s", dwarf_errmsg(de));
				goto next_abbrev;
			}
			printf("      %s    %s\n", tag_str,
			    flag ? "[has children]" : "[no children]");
			for (j = 0; (Dwarf_Unsigned) j < attr_count; j++) {
				if (dwarf_get_abbrev_entry(ab, (Dwarf_Signed) j,
				    &attr, &form, &atoff, &de) != DW_DLV_OK) {
					warnx("dwarf_get_abbrev_entry failed:"
					    " %s", dwarf_errmsg(de));
					continue;
				}
				if (dwarf_get_AT_name(attr, &attr_str) !=
				    DW_DLV_OK) {
					snprintf(unk_attr, sizeof(unk_attr),
					    "[Unknown AT: %#x]", attr);
					attr_str = unk_attr;
				}
				if (dwarf_get_FORM_name(form, &form_str) !=
				    DW_DLV_OK) {
					snprintf(unk_form, sizeof(unk_form),
					    "[Unknown Form: %#x]",
					    (Dwarf_Half) form);
					form_str = unk_form;
				}
				printf("    %-18s %s\n", attr_str, form_str);
			}
		next_abbrev:
			dwarf_dealloc(re->dbg, ab, DW_DLA_ABBREV);
		}
		if (ret != DW_DLV_OK)
			warnx("dwarf_get_abbrev: %s", dwarf_errmsg(de));
	}
	if (ret == DW_DLV_ERROR)
		warnx("dwarf_next_cu_header: %s", dwarf_errmsg(de));
}