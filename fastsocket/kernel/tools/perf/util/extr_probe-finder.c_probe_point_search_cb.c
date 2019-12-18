#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct probe_finder {int /*<<< orphan*/  addr; int /*<<< orphan*/  lno; int /*<<< orphan*/  fname; TYPE_1__* pev; } ;
struct perf_probe_point {scalar_t__ offset; scalar_t__ lazy_line; scalar_t__ line; scalar_t__ file; int /*<<< orphan*/  function; } ;
struct dwarf_callback_param {int /*<<< orphan*/  retval; struct probe_finder* data; } ;
struct TYPE_2__ {struct perf_probe_point point; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  int /*<<< orphan*/  Dwarf_Attribute ;

/* Variables and functions */
 int DWARF_CB_ABORT ; 
 int DWARF_CB_OK ; 
 int /*<<< orphan*/  DW_AT_declaration ; 
 scalar_t__ DW_TAG_subprogram ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  call_probe_finder (int /*<<< orphan*/ *,struct probe_finder*) ; 
 int /*<<< orphan*/  die_compare_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_walk_instances (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ dwarf_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_decl_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_decl_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_diename (int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_entrypc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_func_inline (int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_probe_point_by_line (struct probe_finder*) ; 
 int /*<<< orphan*/  find_probe_point_lazy (int /*<<< orphan*/ *,struct probe_finder*) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe_point_inline_cb ; 
 scalar_t__ strtailcmp (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int probe_point_search_cb(Dwarf_Die *sp_die, void *data)
{
	struct dwarf_callback_param *param = data;
	struct probe_finder *pf = param->data;
	struct perf_probe_point *pp = &pf->pev->point;
	Dwarf_Attribute attr;

	/* Check tag and diename */
	if (dwarf_tag(sp_die) != DW_TAG_subprogram ||
	    !die_compare_name(sp_die, pp->function) ||
	    dwarf_attr(sp_die, DW_AT_declaration, &attr))
		return DWARF_CB_OK;

	/* Check declared file */
	if (pp->file && strtailcmp(pp->file, dwarf_decl_file(sp_die)))
		return DWARF_CB_OK;

	pf->fname = dwarf_decl_file(sp_die);
	if (pp->line) { /* Function relative line */
		dwarf_decl_line(sp_die, &pf->lno);
		pf->lno += pp->line;
		param->retval = find_probe_point_by_line(pf);
	} else if (!dwarf_func_inline(sp_die)) {
		/* Real function */
		if (pp->lazy_line)
			param->retval = find_probe_point_lazy(sp_die, pf);
		else {
			if (dwarf_entrypc(sp_die, &pf->addr) != 0) {
				pr_warning("Failed to get entry address of "
					   "%s.\n", dwarf_diename(sp_die));
				param->retval = -ENOENT;
				return DWARF_CB_ABORT;
			}
			pf->addr += pp->offset;
			/* TODO: Check the address in this function */
			param->retval = call_probe_finder(sp_die, pf);
		}
	} else
		/* Inlined function: search instances */
		param->retval = die_walk_instances(sp_die,
					probe_point_inline_cb, (void *)pf);

	return DWARF_CB_ABORT; /* Exit; no same symbol in this CU. */
}