#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ unfolded; } ;
struct hist_entry {scalar_t__ nr_rows; int /*<<< orphan*/  sorted_chain; TYPE_1__ ms; } ;
struct TYPE_5__ {int /*<<< orphan*/  nr_entries; } ;
struct hist_browser {TYPE_3__* hists; TYPE_2__ b; struct hist_entry* he_selection; int /*<<< orphan*/  selection; } ;
struct TYPE_6__ {int /*<<< orphan*/  nr_entries; } ;

/* Variables and functions */
 scalar_t__ callchain__count_rows (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hist_entry__init_have_children (struct hist_entry*) ; 
 scalar_t__ map_symbol__toggle_fold (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hist_browser__toggle_fold(struct hist_browser *browser)
{
	if (map_symbol__toggle_fold(browser->selection)) {
		struct hist_entry *he = browser->he_selection;

		hist_entry__init_have_children(he);
		browser->hists->nr_entries -= he->nr_rows;

		if (he->ms.unfolded)
			he->nr_rows = callchain__count_rows(&he->sorted_chain);
		else
			he->nr_rows = 0;
		browser->hists->nr_entries += he->nr_rows;
		browser->b.nr_entries = browser->hists->nr_entries;

		return true;
	}

	/* If it doesn't have children, no toggling performed */
	return false;
}