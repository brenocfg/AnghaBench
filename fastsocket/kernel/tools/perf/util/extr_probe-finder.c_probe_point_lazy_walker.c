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
struct probe_finder {int lno; scalar_t__ addr; int /*<<< orphan*/  fname; int /*<<< orphan*/  lcache; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  scalar_t__ Dwarf_Addr ;

/* Variables and functions */
 int ENOENT ; 
 int call_probe_finder (int /*<<< orphan*/ *,struct probe_finder*) ; 
 int /*<<< orphan*/ * find_best_scope (struct probe_finder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  line_list__has_line (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,unsigned long long) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 scalar_t__ strtailcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int probe_point_lazy_walker(const char *fname, int lineno,
				   Dwarf_Addr addr, void *data)
{
	struct probe_finder *pf = data;
	Dwarf_Die *sc_die, die_mem;
	int ret;

	if (!line_list__has_line(&pf->lcache, lineno) ||
	    strtailcmp(fname, pf->fname) != 0)
		return 0;

	pr_debug("Probe line found: line:%d addr:0x%llx\n",
		 lineno, (unsigned long long)addr);
	pf->addr = addr;
	pf->lno = lineno;
	sc_die = find_best_scope(pf, &die_mem);
	if (!sc_die) {
		pr_warning("Failed to find scope of probe point.\n");
		return -ENOENT;
	}

	ret = call_probe_finder(sc_die, pf);

	/*
	 * Continue if no error, because the lazy pattern will match
	 * to other lines
	 */
	return ret < 0 ? ret : 0;
}