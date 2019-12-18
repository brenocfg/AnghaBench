#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct symbol {int dummy; } ;
struct perf_sample {int /*<<< orphan*/  period; scalar_t__ callchain; } ;
struct TYPE_7__ {int /*<<< orphan*/  total_period; } ;
struct TYPE_9__ {TYPE_2__ stats; } ;
struct perf_evsel {TYPE_4__ hists; int /*<<< orphan*/  idx; } ;
struct machine {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * sym; } ;
struct hist_entry {TYPE_1__ ms; int /*<<< orphan*/  callchain; } ;
struct annotation {int /*<<< orphan*/ * src; } ;
struct addr_location {int /*<<< orphan*/  addr; int /*<<< orphan*/  thread; } ;
struct TYPE_8__ {scalar_t__ use_callchain; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PERF_RECORD_SAMPLE ; 
 struct hist_entry* __hists__add_entry (TYPE_4__*,struct addr_location*,struct symbol*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int callchain_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callchain_cursor ; 
 int hist_entry__inc_addr_samples (struct hist_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hists__inc_nr_events (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int machine__resolve_callchain (struct machine*,struct perf_evsel*,int /*<<< orphan*/ ,struct perf_sample*,struct symbol**) ; 
 scalar_t__ sort__has_parent ; 
 scalar_t__ sort__has_sym ; 
 scalar_t__ symbol__alloc_hist (int /*<<< orphan*/ *) ; 
 struct annotation* symbol__annotation (int /*<<< orphan*/ *) ; 
 TYPE_3__ symbol_conf ; 
 int use_browser ; 

__attribute__((used)) static int perf_evsel__add_hist_entry(struct perf_evsel *evsel,
				      struct addr_location *al,
				      struct perf_sample *sample,
				      struct machine *machine)
{
	struct symbol *parent = NULL;
	int err = 0;
	struct hist_entry *he;

	if ((sort__has_parent || symbol_conf.use_callchain) && sample->callchain) {
		err = machine__resolve_callchain(machine, evsel, al->thread,
						 sample, &parent);
		if (err)
			return err;
	}

	he = __hists__add_entry(&evsel->hists, al, parent, sample->period);
	if (he == NULL)
		return -ENOMEM;

	if (symbol_conf.use_callchain) {
		err = callchain_append(he->callchain,
				       &callchain_cursor,
				       sample->period);
		if (err)
			return err;
	}
	/*
	 * Only in the newt browser we are doing integrated annotation,
	 * so we don't allocated the extra space needed because the stdio
	 * code will not use it.
	 */
	if (he->ms.sym != NULL && use_browser == 1 && sort__has_sym) {
		struct annotation *notes = symbol__annotation(he->ms.sym);

		assert(evsel != NULL);

		err = -ENOMEM;
		if (notes->src == NULL && symbol__alloc_hist(he->ms.sym) < 0)
			goto out;

		err = hist_entry__inc_addr_samples(he, evsel->idx, al->addr);
	}

	evsel->hists.stats.total_period += sample->period;
	hists__inc_nr_events(&evsel->hists, PERF_RECORD_SAMPLE);
out:
	return err;
}