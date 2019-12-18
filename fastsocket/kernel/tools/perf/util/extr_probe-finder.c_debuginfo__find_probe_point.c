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
struct perf_probe_point {int line; unsigned long offset; int /*<<< orphan*/ * function; int /*<<< orphan*/ * file; } ;
struct debuginfo {unsigned long bias; int /*<<< orphan*/  dbg; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  unsigned long Dwarf_Addr ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  cu_find_lineinfo (int /*<<< orphan*/ *,unsigned long,char const**,int*) ; 
 scalar_t__ die_find_inlinefunc (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 
 scalar_t__ die_find_realfunc (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 
 int die_get_call_lineno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_addrdie (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_decl_line (int /*<<< orphan*/ *,int*) ; 
 char* dwarf_diename (int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_entrypc (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warning (char*,unsigned long) ; 
 void* strdup (char const*) ; 

int debuginfo__find_probe_point(struct debuginfo *self, unsigned long addr,
				struct perf_probe_point *ppt)
{
	Dwarf_Die cudie, spdie, indie;
	Dwarf_Addr _addr, baseaddr;
	const char *fname = NULL, *func = NULL, *tmp;
	int baseline = 0, lineno = 0, ret = 0;

	/* Adjust address with bias */
	addr += self->bias;

	/* Find cu die */
	if (!dwarf_addrdie(self->dbg, (Dwarf_Addr)addr - self->bias, &cudie)) {
		pr_warning("Failed to find debug information for address %lx\n",
			   addr);
		ret = -EINVAL;
		goto end;
	}

	/* Find a corresponding line (filename and lineno) */
	cu_find_lineinfo(&cudie, addr, &fname, &lineno);
	/* Don't care whether it failed or not */

	/* Find a corresponding function (name, baseline and baseaddr) */
	if (die_find_realfunc(&cudie, (Dwarf_Addr)addr, &spdie)) {
		/* Get function entry information */
		tmp = dwarf_diename(&spdie);
		if (!tmp ||
		    dwarf_entrypc(&spdie, &baseaddr) != 0 ||
		    dwarf_decl_line(&spdie, &baseline) != 0)
			goto post;
		func = tmp;

		if (addr == (unsigned long)baseaddr)
			/* Function entry - Relative line number is 0 */
			lineno = baseline;
		else if (die_find_inlinefunc(&spdie, (Dwarf_Addr)addr,
					     &indie)) {
			if (dwarf_entrypc(&indie, &_addr) == 0 &&
			    _addr == addr)
				/*
				 * addr is at an inline function entry.
				 * In this case, lineno should be the call-site
				 * line number.
				 */
				lineno = die_get_call_lineno(&indie);
			else {
				/*
				 * addr is in an inline function body.
				 * Since lineno points one of the lines
				 * of the inline function, baseline should
				 * be the entry line of the inline function.
				 */
				tmp = dwarf_diename(&indie);
				if (tmp &&
				    dwarf_decl_line(&spdie, &baseline) == 0)
					func = tmp;
			}
		}
	}

post:
	/* Make a relative line number or an offset */
	if (lineno)
		ppt->line = lineno - baseline;
	else if (func)
		ppt->offset = addr - (unsigned long)baseaddr;

	/* Duplicate strings */
	if (func) {
		ppt->function = strdup(func);
		if (ppt->function == NULL) {
			ret = -ENOMEM;
			goto end;
		}
	}
	if (fname) {
		ppt->file = strdup(fname);
		if (ppt->file == NULL) {
			if (ppt->function) {
				free(ppt->function);
				ppt->function = NULL;
			}
			ret = -ENOMEM;
			goto end;
		}
	}
end:
	if (ret == 0 && (fname || func))
		ret = 1;	/* Found a point */
	return ret;
}