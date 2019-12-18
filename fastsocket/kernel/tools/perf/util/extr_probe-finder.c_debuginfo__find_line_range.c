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
struct pubname_callback_param {scalar_t__ found; int /*<<< orphan*/ * sp_die; int /*<<< orphan*/ * cu_die; int /*<<< orphan*/  file; scalar_t__ function; } ;
struct line_range {int /*<<< orphan*/  path; int /*<<< orphan*/  comp_dir; int /*<<< orphan*/  end; int /*<<< orphan*/  start; scalar_t__ function; int /*<<< orphan*/  file; } ;
struct line_finder {int found; int /*<<< orphan*/  cu_die; int /*<<< orphan*/  lno_e; int /*<<< orphan*/  lno_s; scalar_t__ fname; int /*<<< orphan*/  sp_die; struct line_range* lr; } ;
struct dwarf_callback_param {void* data; int /*<<< orphan*/  retval; } ;
struct debuginfo {int /*<<< orphan*/  dbg; } ;
typedef  scalar_t__ Dwarf_Off ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ cu_find_realpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* cu_get_comp_dir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_getpubnames (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pubname_callback_param*,int /*<<< orphan*/ ) ; 
 scalar_t__ dwarf_nextcu (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dwarf_offdie (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int find_line_range_by_func (struct line_finder*) ; 
 int find_line_range_by_line (int /*<<< orphan*/ *,struct line_finder*) ; 
 int /*<<< orphan*/  line_range_search_cb (int /*<<< orphan*/ *,struct dwarf_callback_param*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pubname_search_cb ; 
 int /*<<< orphan*/  strdup (char const*) ; 

int debuginfo__find_line_range(struct debuginfo *self, struct line_range *lr)
{
	struct line_finder lf = {.lr = lr, .found = 0};
	int ret = 0;
	Dwarf_Off off = 0, noff;
	size_t cuhl;
	Dwarf_Die *diep;
	const char *comp_dir;

	/* Fastpath: lookup by function name from .debug_pubnames section */
	if (lr->function) {
		struct pubname_callback_param pubname_param = {
			.function = lr->function, .file = lr->file,
			.cu_die = &lf.cu_die, .sp_die = &lf.sp_die, .found = 0};
		struct dwarf_callback_param line_range_param = {
			.data = (void *)&lf, .retval = 0};

		dwarf_getpubnames(self->dbg, pubname_search_cb,
				  &pubname_param, 0);
		if (pubname_param.found) {
			line_range_search_cb(&lf.sp_die, &line_range_param);
			if (lf.found)
				goto found;
		}
	}

	/* Loop on CUs (Compilation Unit) */
	while (!lf.found && ret >= 0) {
		if (dwarf_nextcu(self->dbg, off, &noff, &cuhl,
				 NULL, NULL, NULL) != 0)
			break;

		/* Get the DIE(Debugging Information Entry) of this CU */
		diep = dwarf_offdie(self->dbg, off + cuhl, &lf.cu_die);
		if (!diep)
			continue;

		/* Check if target file is included. */
		if (lr->file)
			lf.fname = cu_find_realpath(&lf.cu_die, lr->file);
		else
			lf.fname = 0;

		if (!lr->file || lf.fname) {
			if (lr->function)
				ret = find_line_range_by_func(&lf);
			else {
				lf.lno_s = lr->start;
				lf.lno_e = lr->end;
				ret = find_line_range_by_line(NULL, &lf);
			}
		}
		off = noff;
	}

found:
	/* Store comp_dir */
	if (lf.found) {
		comp_dir = cu_get_comp_dir(&lf.cu_die);
		if (comp_dir) {
			lr->comp_dir = strdup(comp_dir);
			if (!lr->comp_dir)
				ret = -ENOMEM;
		}
	}

	pr_debug("path: %s\n", lr->path);
	return (ret < 0) ? ret : lf.found;
}