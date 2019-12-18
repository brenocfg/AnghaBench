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
struct perf_top {int /*<<< orphan*/  hide_kernel_symbols; int /*<<< orphan*/  hide_user_symbols; TYPE_2__* sym_evsel; TYPE_1__* evlist; } ;
struct TYPE_4__ {int /*<<< orphan*/  hists; } ;
struct TYPE_3__ {TYPE_2__* selected; } ;

/* Variables and functions */
 int /*<<< orphan*/  hists__collapse_resort_threaded (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hists__decay_entries_threaded (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hists__output_resort_threaded (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_top__reset_sample_counters (struct perf_top*) ; 

__attribute__((used)) static void perf_top__sort_new_samples(void *arg)
{
	struct perf_top *t = arg;
	perf_top__reset_sample_counters(t);

	if (t->evlist->selected != NULL)
		t->sym_evsel = t->evlist->selected;

	hists__collapse_resort_threaded(&t->sym_evsel->hists);
	hists__output_resort_threaded(&t->sym_evsel->hists);
	hists__decay_entries_threaded(&t->sym_evsel->hists,
				      t->hide_user_symbols,
				      t->hide_kernel_symbols);
}