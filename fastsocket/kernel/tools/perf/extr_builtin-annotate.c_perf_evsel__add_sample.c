#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct perf_sample {scalar_t__ period; } ;
struct TYPE_11__ {int /*<<< orphan*/  total_period; } ;
struct TYPE_13__ {TYPE_4__ stats; } ;
struct perf_evsel {TYPE_6__ hists; int /*<<< orphan*/  idx; } ;
struct perf_annotate {int /*<<< orphan*/ * sym_hist_filter; } ;
struct TYPE_10__ {int /*<<< orphan*/ * sym; } ;
struct hist_entry {TYPE_3__ ms; } ;
struct annotation {int /*<<< orphan*/ * src; } ;
struct addr_location {int /*<<< orphan*/  addr; TYPE_5__* sym; TYPE_2__* map; } ;
struct TYPE_12__ {int /*<<< orphan*/  rb_node; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {size_t type; TYPE_1__* dso; } ;
struct TYPE_8__ {int /*<<< orphan*/ * symbols; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PERF_RECORD_SAMPLE ; 
 struct hist_entry* __hists__add_entry (TYPE_6__*,struct addr_location*,int /*<<< orphan*/ *,int) ; 
 int hist_entry__inc_addr_samples (struct hist_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hists__inc_nr_events (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ symbol__alloc_hist (int /*<<< orphan*/ *) ; 
 struct annotation* symbol__annotation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol__delete (TYPE_5__*) ; 

__attribute__((used)) static int perf_evsel__add_sample(struct perf_evsel *evsel,
				  struct perf_sample *sample,
				  struct addr_location *al,
				  struct perf_annotate *ann)
{
	struct hist_entry *he;
	int ret;

	if (ann->sym_hist_filter != NULL &&
	    (al->sym == NULL ||
	     strcmp(ann->sym_hist_filter, al->sym->name) != 0)) {
		/* We're only interested in a symbol named sym_hist_filter */
		if (al->sym != NULL) {
			rb_erase(&al->sym->rb_node,
				 &al->map->dso->symbols[al->map->type]);
			symbol__delete(al->sym);
		}
		return 0;
	}

	he = __hists__add_entry(&evsel->hists, al, NULL, 1);
	if (he == NULL)
		return -ENOMEM;

	ret = 0;
	if (he->ms.sym != NULL) {
		struct annotation *notes = symbol__annotation(he->ms.sym);
		if (notes->src == NULL && symbol__alloc_hist(he->ms.sym) < 0)
			return -ENOMEM;

		ret = hist_entry__inc_addr_samples(he, evsel->idx, al->addr);
	}

	evsel->hists.stats.total_period += sample->period;
	hists__inc_nr_events(&evsel->hists, PERF_RECORD_SAMPLE);
	return ret;
}