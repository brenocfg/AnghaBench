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
struct pevent_record {unsigned long long ts; int cpu; int size; void* data; } ;
struct pevent {int /*<<< orphan*/  latency_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  latency_format ; 
 int pevent_data_pid (struct pevent*,struct pevent_record*) ; 
 int /*<<< orphan*/  pevent_pid_is_registered (struct pevent*,int) ; 
 int /*<<< orphan*/  pevent_print_event (struct pevent*,struct trace_seq*,struct pevent_record*) ; 
 int /*<<< orphan*/  pevent_register_comm (struct pevent*,char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  trace_seq_do_printf (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_init (struct trace_seq*) ; 

void print_event(struct pevent *pevent, int cpu, void *data, int size,
		 unsigned long long nsecs, char *comm)
{
	struct pevent_record record;
	struct trace_seq s;
	int pid;

	pevent->latency_format = latency_format;

	record.ts = nsecs;
	record.cpu = cpu;
	record.size = size;
	record.data = data;
	pid = pevent_data_pid(pevent, &record);

	if (!pevent_pid_is_registered(pevent, pid))
		pevent_register_comm(pevent, comm, pid);

	trace_seq_init(&s);
	pevent_print_event(pevent, &s, &record);
	trace_seq_do_printf(&s);
	printf("\n");
}