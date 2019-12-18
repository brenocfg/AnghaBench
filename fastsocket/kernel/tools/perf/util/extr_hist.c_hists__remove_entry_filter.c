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
struct TYPE_4__ {int /*<<< orphan*/ * nr_events; int /*<<< orphan*/  total_period; } ;
struct hists {TYPE_1__ stats; scalar_t__ nr_entries; } ;
struct TYPE_5__ {scalar_t__ nr_events; scalar_t__ period; } ;
struct TYPE_6__ {scalar_t__ unfolded; } ;
struct hist_entry {int filtered; TYPE_2__ stat; scalar_t__ row_offset; scalar_t__ nr_rows; TYPE_3__ ms; } ;
typedef  enum hist_filter { ____Placeholder_hist_filter } hist_filter ;

/* Variables and functions */
 size_t PERF_RECORD_SAMPLE ; 
 int /*<<< orphan*/  hists__calc_col_len (struct hists*,struct hist_entry*) ; 

__attribute__((used)) static void hists__remove_entry_filter(struct hists *hists, struct hist_entry *h,
				       enum hist_filter filter)
{
	h->filtered &= ~(1 << filter);
	if (h->filtered)
		return;

	++hists->nr_entries;
	if (h->ms.unfolded)
		hists->nr_entries += h->nr_rows;
	h->row_offset = 0;
	hists->stats.total_period += h->stat.period;
	hists->stats.nr_events[PERF_RECORD_SAMPLE] += h->stat.nr_events;

	hists__calc_col_len(hists, h);
}