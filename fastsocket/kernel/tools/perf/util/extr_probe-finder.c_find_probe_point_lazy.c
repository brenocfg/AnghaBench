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
struct probe_finder {TYPE_2__* pev; int /*<<< orphan*/  fname; int /*<<< orphan*/  lcache; } ;
struct TYPE_3__ {int /*<<< orphan*/  lazy_line; } ;
struct TYPE_4__ {TYPE_1__ point; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int die_walk_lines (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct probe_finder*) ; 
 int find_lazy_match_lines (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  probe_point_lazy_walker ; 

__attribute__((used)) static int find_probe_point_lazy(Dwarf_Die *sp_die, struct probe_finder *pf)
{
	int ret = 0;

	if (list_empty(&pf->lcache)) {
		/* Matching lazy line pattern */
		ret = find_lazy_match_lines(&pf->lcache, pf->fname,
					    pf->pev->point.lazy_line);
		if (ret <= 0)
			return ret;
	}

	return die_walk_lines(sp_die, probe_point_lazy_walker, pf);
}