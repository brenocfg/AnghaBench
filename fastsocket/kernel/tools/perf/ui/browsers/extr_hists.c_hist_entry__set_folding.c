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
struct TYPE_2__ {scalar_t__ has_children; } ;
struct hist_entry {int nr_rows; int /*<<< orphan*/  sorted_chain; TYPE_1__ ms; } ;

/* Variables and functions */
 int callchain__set_folding (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hist_entry__init_have_children (struct hist_entry*) ; 
 int /*<<< orphan*/  map_symbol__set_folding (TYPE_1__*,int) ; 

__attribute__((used)) static void hist_entry__set_folding(struct hist_entry *he, bool unfold)
{
	hist_entry__init_have_children(he);
	map_symbol__set_folding(&he->ms, unfold);

	if (he->ms.has_children) {
		int n = callchain__set_folding(&he->sorted_chain, unfold);
		he->nr_rows = unfold ? n : 0;
	} else
		he->nr_rows = 0;
}