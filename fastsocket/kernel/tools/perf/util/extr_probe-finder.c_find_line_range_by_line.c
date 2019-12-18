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
struct line_finder {int found; TYPE_1__* lr; int /*<<< orphan*/  cu_die; } ;
struct TYPE_2__ {int /*<<< orphan*/ * path; int /*<<< orphan*/  line_list; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int die_walk_lines (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct line_finder*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  line_range_walk_cb ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int find_line_range_by_line(Dwarf_Die *sp_die, struct line_finder *lf)
{
	int ret;

	ret = die_walk_lines(sp_die ?: &lf->cu_die, line_range_walk_cb, lf);

	/* Update status */
	if (ret >= 0)
		if (!list_empty(&lf->lr->line_list))
			ret = lf->found = 1;
		else
			ret = 0;	/* Lines are not found */
	else {
		free(lf->lr->path);
		lf->lr->path = NULL;
	}
	return ret;
}