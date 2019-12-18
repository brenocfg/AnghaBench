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
typedef  int /*<<< orphan*/  Dwarf_Line ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  scalar_t__ Dwarf_Addr ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/ * dwarf_getsrc_die (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ dwarf_lineaddr (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ dwarf_lineno (int /*<<< orphan*/ *,int*) ; 
 char* dwarf_linesrc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int cu_find_lineinfo(Dwarf_Die *cu_die, unsigned long addr,
		    const char **fname, int *lineno)
{
	Dwarf_Line *line;
	Dwarf_Addr laddr;

	line = dwarf_getsrc_die(cu_die, (Dwarf_Addr)addr);
	if (line && dwarf_lineaddr(line, &laddr) == 0 &&
	    addr == (unsigned long)laddr && dwarf_lineno(line, lineno) == 0) {
		*fname = dwarf_linesrc(line, NULL, NULL);
		if (!*fname)
			/* line number is useless without filename */
			*lineno = 0;
	}

	return *lineno ?: -ENOENT;
}