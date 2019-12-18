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
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct ring_buffer_event {int dummy; } ;

/* Variables and functions */
 unsigned long NSEC_PER_MSEC ; 
 scalar_t__ RUN_TIME ; 
 int /*<<< orphan*/  USEC_PER_MSEC ; 
 unsigned long long USEC_PER_SEC ; 
 int /*<<< orphan*/  buffer ; 
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ consumer ; 
 scalar_t__ disable_reader ; 
 int /*<<< orphan*/  do_div (unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ kill_test ; 
 unsigned long long read ; 
 int /*<<< orphan*/  read_done ; 
 scalar_t__ read_events ; 
 int /*<<< orphan*/  read_start ; 
 int reader_finish ; 
 unsigned long long ring_buffer_entries (int /*<<< orphan*/ ) ; 
 int* ring_buffer_event_data (struct ring_buffer_event*) ; 
 struct ring_buffer_event* ring_buffer_lock_reserve (int /*<<< orphan*/ ,int) ; 
 unsigned long long ring_buffer_overruns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ring_buffer_unlock_commit (int /*<<< orphan*/ ,struct ring_buffer_event*) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  trace_printk (char*,...) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (scalar_t__) ; 
 int wakeup_interval ; 

__attribute__((used)) static void ring_buffer_producer(void)
{
	struct timeval start_tv;
	struct timeval end_tv;
	unsigned long long time;
	unsigned long long entries;
	unsigned long long overruns;
	unsigned long missed = 0;
	unsigned long hit = 0;
	unsigned long avg;
	int cnt = 0;

	/*
	 * Hammer the buffer for 10 secs (this may
	 * make the system stall)
	 */
	trace_printk("Starting ring buffer hammer\n");
	do_gettimeofday(&start_tv);
	do {
		struct ring_buffer_event *event;
		int *entry;

		event = ring_buffer_lock_reserve(buffer, 10);
		if (!event) {
			missed++;
		} else {
			hit++;
			entry = ring_buffer_event_data(event);
			*entry = smp_processor_id();
			ring_buffer_unlock_commit(buffer, event);
		}
		do_gettimeofday(&end_tv);

		cnt++;
		if (consumer && !(cnt % wakeup_interval))
			wake_up_process(consumer);

#ifndef CONFIG_PREEMPT
		/*
		 * If we are a non preempt kernel, the 10 second run will
		 * stop everything while it runs. Instead, we will call
		 * cond_resched and also add any time that was lost by a
		 * rescedule.
		 *
		 * Do a cond resched at the same frequency we would wake up
		 * the reader.
		 */
		if (cnt % wakeup_interval)
			cond_resched();
#endif

	} while (end_tv.tv_sec < (start_tv.tv_sec + RUN_TIME) && !kill_test);
	trace_printk("End ring buffer hammer\n");

	if (consumer) {
		/* Init both completions here to avoid races */
		init_completion(&read_start);
		init_completion(&read_done);
		/* the completions must be visible before the finish var */
		smp_wmb();
		reader_finish = 1;
		/* finish var visible before waking up the consumer */
		smp_wmb();
		wake_up_process(consumer);
		wait_for_completion(&read_done);
	}

	time = end_tv.tv_sec - start_tv.tv_sec;
	time *= USEC_PER_SEC;
	time += (long long)((long)end_tv.tv_usec - (long)start_tv.tv_usec);

	entries = ring_buffer_entries(buffer);
	overruns = ring_buffer_overruns(buffer);

	if (kill_test)
		trace_printk("ERROR!\n");
	trace_printk("Time:     %lld (usecs)\n", time);
	trace_printk("Overruns: %lld\n", overruns);
	if (disable_reader)
		trace_printk("Read:     (reader disabled)\n");
	else
		trace_printk("Read:     %ld  (by %s)\n", read,
			read_events ? "events" : "pages");
	trace_printk("Entries:  %lld\n", entries);
	trace_printk("Total:    %lld\n", entries + overruns + read);
	trace_printk("Missed:   %ld\n", missed);
	trace_printk("Hit:      %ld\n", hit);

	/* Convert time from usecs to millisecs */
	do_div(time, USEC_PER_MSEC);
	if (time)
		hit /= (long)time;
	else
		trace_printk("TIME IS ZERO??\n");

	trace_printk("Entries per millisec: %ld\n", hit);

	if (hit) {
		/* Calculate the average time in nanosecs */
		avg = NSEC_PER_MSEC / hit;
		trace_printk("%ld ns per entry\n", avg);
	}

	if (missed) {
		if (time)
			missed /= (long)time;

		trace_printk("Total iterations per millisec: %ld\n",
			     hit + missed);

		/* it is possible that hit + missed will overflow and be zero */
		if (!(hit + missed)) {
			trace_printk("hit + missed overflowed and totalled zero!\n");
			hit--; /* make it non zero */
		}

		/* Caculate the average time in nanosecs */
		avg = NSEC_PER_MSEC / (hit + missed);
		trace_printk("%ld ns per entry\n", avg);
	}
}