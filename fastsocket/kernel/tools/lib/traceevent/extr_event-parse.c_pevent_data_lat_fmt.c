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
struct trace_seq {int dummy; } ;
struct pevent_record {void* data; } ;
struct pevent {int dummy; } ;

/* Variables and functions */
 unsigned int TRACE_FLAG_HARDIRQ ; 
 unsigned int TRACE_FLAG_IRQS_NOSUPPORT ; 
 unsigned int TRACE_FLAG_IRQS_OFF ; 
 unsigned int TRACE_FLAG_NEED_RESCHED ; 
 unsigned int TRACE_FLAG_SOFTIRQ ; 
 unsigned int parse_common_flags (struct pevent*,void*) ; 
 int parse_common_lock_depth (struct pevent*,void*) ; 
 int parse_common_migrate_disable (struct pevent*,void*) ; 
 unsigned int parse_common_pc (struct pevent*,void*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,int,...) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,char) ; 
 int /*<<< orphan*/  trace_seq_terminate (struct trace_seq*) ; 

void pevent_data_lat_fmt(struct pevent *pevent,
			 struct trace_seq *s, struct pevent_record *record)
{
	static int check_lock_depth = 1;
	static int check_migrate_disable = 1;
	static int lock_depth_exists;
	static int migrate_disable_exists;
	unsigned int lat_flags;
	unsigned int pc;
	int lock_depth;
	int migrate_disable;
	int hardirq;
	int softirq;
	void *data = record->data;

	lat_flags = parse_common_flags(pevent, data);
	pc = parse_common_pc(pevent, data);
	/* lock_depth may not always exist */
	if (lock_depth_exists)
		lock_depth = parse_common_lock_depth(pevent, data);
	else if (check_lock_depth) {
		lock_depth = parse_common_lock_depth(pevent, data);
		if (lock_depth < 0)
			check_lock_depth = 0;
		else
			lock_depth_exists = 1;
	}

	/* migrate_disable may not always exist */
	if (migrate_disable_exists)
		migrate_disable = parse_common_migrate_disable(pevent, data);
	else if (check_migrate_disable) {
		migrate_disable = parse_common_migrate_disable(pevent, data);
		if (migrate_disable < 0)
			check_migrate_disable = 0;
		else
			migrate_disable_exists = 1;
	}

	hardirq = lat_flags & TRACE_FLAG_HARDIRQ;
	softirq = lat_flags & TRACE_FLAG_SOFTIRQ;

	trace_seq_printf(s, "%c%c%c",
	       (lat_flags & TRACE_FLAG_IRQS_OFF) ? 'd' :
	       (lat_flags & TRACE_FLAG_IRQS_NOSUPPORT) ?
	       'X' : '.',
	       (lat_flags & TRACE_FLAG_NEED_RESCHED) ?
	       'N' : '.',
	       (hardirq && softirq) ? 'H' :
	       hardirq ? 'h' : softirq ? 's' : '.');

	if (pc)
		trace_seq_printf(s, "%x", pc);
	else
		trace_seq_putc(s, '.');

	if (migrate_disable_exists) {
		if (migrate_disable < 0)
			trace_seq_putc(s, '.');
		else
			trace_seq_printf(s, "%d", migrate_disable);
	}

	if (lock_depth_exists) {
		if (lock_depth < 0)
			trace_seq_putc(s, '.');
		else
			trace_seq_printf(s, "%d", lock_depth);
	}

	trace_seq_terminate(s);
}