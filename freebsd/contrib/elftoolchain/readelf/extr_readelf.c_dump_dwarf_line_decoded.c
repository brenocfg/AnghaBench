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
typedef  char* uintmax_t ;
struct readelf {int /*<<< orphan*/  dbg; } ;
typedef  int Dwarf_Unsigned ;
typedef  int Dwarf_Signed ;
typedef  int /*<<< orphan*/  Dwarf_Line ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  scalar_t__ Dwarf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_comp_dir ; 
 int /*<<< orphan*/  DW_AT_name ; 
 int DW_DLV_OK ; 
 char* basename (char*) ; 
 int dwarf_attrval_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *) ; 
 int dwarf_line_srcfileno (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int dwarf_lineaddr (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int dwarf_lineno (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int dwarf_next_cu_header (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dwarf_siblingof (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dwarf_srcfiles (int /*<<< orphan*/ ,char***,int*,int /*<<< orphan*/ *) ; 
 int dwarf_srclines (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void
dump_dwarf_line_decoded(struct readelf *re)
{
	Dwarf_Die die;
	Dwarf_Line *linebuf, ln;
	Dwarf_Addr lineaddr;
	Dwarf_Signed linecount, srccount;
	Dwarf_Unsigned lineno, fn;
	Dwarf_Error de;
	const char *dir, *file;
	char **srcfiles;
	int i, ret;

	printf("Decoded dump of debug contents of section .debug_line:\n\n");
	while ((ret = dwarf_next_cu_header(re->dbg, NULL, NULL, NULL, NULL,
	    NULL, &de)) == DW_DLV_OK) {
		if (dwarf_siblingof(re->dbg, NULL, &die, &de) != DW_DLV_OK)
			continue;
		if (dwarf_attrval_string(die, DW_AT_name, &file, &de) !=
		    DW_DLV_OK)
			file = NULL;
		if (dwarf_attrval_string(die, DW_AT_comp_dir, &dir, &de) !=
		    DW_DLV_OK)
			dir = NULL;
		printf("CU: ");
		if (dir && file && file[0] != '/')
			printf("%s/", dir);
		if (file)
			printf("%s", file);
		putchar('\n');
		printf("%-37s %11s   %s\n", "Filename", "Line Number",
		    "Starting Address");
		if (dwarf_srclines(die, &linebuf, &linecount, &de) != DW_DLV_OK)
			continue;
		if (dwarf_srcfiles(die, &srcfiles, &srccount, &de) != DW_DLV_OK)
			continue;
		for (i = 0; i < linecount; i++) {
			ln = linebuf[i];
			if (dwarf_line_srcfileno(ln, &fn, &de) != DW_DLV_OK)
				continue;
			if (dwarf_lineno(ln, &lineno, &de) != DW_DLV_OK)
				continue;
			if (dwarf_lineaddr(ln, &lineaddr, &de) != DW_DLV_OK)
				continue;
			printf("%-37s %11ju %#18jx\n",
			    basename(srcfiles[fn - 1]), (uintmax_t) lineno,
			    (uintmax_t) lineaddr);
		}
		putchar('\n');
	}
}