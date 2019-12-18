#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timespec {int tv_nsec; int tv_sec; } ;
struct seq_file {int dummy; } ;
struct entry {int timer_flag; scalar_t__ count; scalar_t__ expire_func; scalar_t__ start_func; int /*<<< orphan*/  comm; int /*<<< orphan*/  pid; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int TIMER_STATS_FLAG_DEFERRABLE ; 
 long atomic_read (int /*<<< orphan*/ *) ; 
 struct entry* entries ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct timespec ktime_to_timespec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nr_entries ; 
 int /*<<< orphan*/  overflow_count ; 
 int /*<<< orphan*/  print_name_offset (struct seq_file*,unsigned long) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,long,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  show_mutex ; 
 int /*<<< orphan*/  time_start ; 
 int /*<<< orphan*/  time_stop ; 
 scalar_t__ timer_stats_active ; 

__attribute__((used)) static int tstats_show(struct seq_file *m, void *v)
{
	struct timespec period;
	struct entry *entry;
	unsigned long ms;
	long events = 0;
	ktime_t time;
	int i;

	mutex_lock(&show_mutex);
	/*
	 * If still active then calculate up to now:
	 */
	if (timer_stats_active)
		time_stop = ktime_get();

	time = ktime_sub(time_stop, time_start);

	period = ktime_to_timespec(time);
	ms = period.tv_nsec / 1000000;

	seq_puts(m, "Timer Stats Version: v0.2\n");
	seq_printf(m, "Sample period: %ld.%03ld s\n", period.tv_sec, ms);
	if (atomic_read(&overflow_count))
		seq_printf(m, "Overflow: %d entries\n",
			atomic_read(&overflow_count));

	for (i = 0; i < nr_entries; i++) {
		entry = entries + i;
 		if (entry->timer_flag & TIMER_STATS_FLAG_DEFERRABLE) {
			seq_printf(m, "%4luD, %5d %-16s ",
				entry->count, entry->pid, entry->comm);
		} else {
			seq_printf(m, " %4lu, %5d %-16s ",
				entry->count, entry->pid, entry->comm);
		}

		print_name_offset(m, (unsigned long)entry->start_func);
		seq_puts(m, " (");
		print_name_offset(m, (unsigned long)entry->expire_func);
		seq_puts(m, ")\n");

		events += entry->count;
	}

	ms += period.tv_sec * 1000;
	if (!ms)
		ms = 1;

	if (events && period.tv_sec)
		seq_printf(m, "%ld total events, %ld.%03ld events/sec\n",
			   events, events * 1000 / ms,
			   (events * 1000000 / ms) % 1000);
	else
		seq_printf(m, "%ld total events\n", events);

	mutex_unlock(&show_mutex);

	return 0;
}