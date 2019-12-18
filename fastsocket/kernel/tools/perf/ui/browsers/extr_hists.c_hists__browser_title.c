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
typedef  int /*<<< orphan*/  u64 ;
struct thread {char* comm; int /*<<< orphan*/  pid; scalar_t__ comm_set; } ;
struct TYPE_2__ {unsigned long* nr_events; int /*<<< orphan*/  total_period; } ;
struct hists {char* uid_filter_str; TYPE_1__ stats; struct thread* thread_filter; struct dso* dso_filter; } ;
struct dso {int /*<<< orphan*/  short_name; } ;

/* Variables and functions */
 size_t PERF_RECORD_SAMPLE ; 
 unsigned long convert_unit (unsigned long,char*) ; 
 int scnprintf (char*,size_t,char*,...) ; 
 scalar_t__ snprintf (char*,size_t,char*,char*) ; 

__attribute__((used)) static int hists__browser_title(struct hists *hists, char *bf, size_t size,
				const char *ev_name)
{
	char unit;
	int printed;
	const struct dso *dso = hists->dso_filter;
	const struct thread *thread = hists->thread_filter;
	unsigned long nr_samples = hists->stats.nr_events[PERF_RECORD_SAMPLE];
	u64 nr_events = hists->stats.total_period;

	nr_samples = convert_unit(nr_samples, &unit);
	printed = scnprintf(bf, size,
			   "Samples: %lu%c of event '%s', Event count (approx.): %lu",
			   nr_samples, unit, ev_name, nr_events);


	if (hists->uid_filter_str)
		printed += snprintf(bf + printed, size - printed,
				    ", UID: %s", hists->uid_filter_str);
	if (thread)
		printed += scnprintf(bf + printed, size - printed,
				    ", Thread: %s(%d)",
				    (thread->comm_set ? thread->comm : ""),
				    thread->pid);
	if (dso)
		printed += scnprintf(bf + printed, size - printed,
				    ", DSO: %s", dso->short_name);
	return printed;
}