#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct probe_finder {int /*<<< orphan*/  addr; int /*<<< orphan*/  cu_die; int /*<<< orphan*/  lno; int /*<<< orphan*/  fname; TYPE_2__* pev; } ;
struct find_scope_param {int found; int /*<<< orphan*/ * die_mem; int /*<<< orphan*/  diff; int /*<<< orphan*/  line; int /*<<< orphan*/  file; int /*<<< orphan*/  function; } ;
struct TYPE_3__ {int /*<<< orphan*/  function; } ;
struct TYPE_4__ {TYPE_1__ point; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  cu_walk_functions_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct find_scope_param*) ; 
 int /*<<< orphan*/  find_best_scope_cb ; 

__attribute__((used)) static Dwarf_Die *find_best_scope(struct probe_finder *pf, Dwarf_Die *die_mem)
{
	struct find_scope_param fsp = {
		.function = pf->pev->point.function,
		.file = pf->fname,
		.line = pf->lno,
		.diff = INT_MAX,
		.die_mem = die_mem,
		.found = false,
	};

	cu_walk_functions_at(&pf->cu_die, pf->addr, find_best_scope_cb, &fsp);

	return fsp.found ? die_mem : NULL;
}