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
struct symbol {char* name; } ;
struct perf_top {int sym_pcnt_filter; TYPE_2__* sym_evsel; scalar_t__ zero; int /*<<< orphan*/  print_entries; struct hist_entry* sym_filter_entry; } ;
struct TYPE_3__ {int /*<<< orphan*/  map; struct symbol* sym; } ;
struct hist_entry {TYPE_1__ ms; } ;
struct annotation {int /*<<< orphan*/  lock; int /*<<< orphan*/ * src; } ;
struct TYPE_4__ {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 char* perf_evsel__name (TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol__annotate_decay_histogram (struct symbol*,int /*<<< orphan*/ ) ; 
 int symbol__annotate_printf (struct symbol*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  symbol__annotate_zero_histogram (struct symbol*,int /*<<< orphan*/ ) ; 
 struct annotation* symbol__annotation (struct symbol*) ; 

__attribute__((used)) static void perf_top__show_details(struct perf_top *top)
{
	struct hist_entry *he = top->sym_filter_entry;
	struct annotation *notes;
	struct symbol *symbol;
	int more;

	if (!he)
		return;

	symbol = he->ms.sym;
	notes = symbol__annotation(symbol);

	pthread_mutex_lock(&notes->lock);

	if (notes->src == NULL)
		goto out_unlock;

	printf("Showing %s for %s\n", perf_evsel__name(top->sym_evsel), symbol->name);
	printf("  Events  Pcnt (>=%d%%)\n", top->sym_pcnt_filter);

	more = symbol__annotate_printf(symbol, he->ms.map, top->sym_evsel->idx,
				       0, top->sym_pcnt_filter, top->print_entries, 4);
	if (top->zero)
		symbol__annotate_zero_histogram(symbol, top->sym_evsel->idx);
	else
		symbol__annotate_decay_histogram(symbol, top->sym_evsel->idx);
	if (more != 0)
		printf("%d lines not displayed, maybe increase display entries [e]\n", more);
out_unlock:
	pthread_mutex_unlock(&notes->lock);
}