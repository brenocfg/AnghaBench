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
struct pevent_record {int cpu; int size; void* data; } ;
struct event_format {int dummy; } ;
typedef  int /*<<< orphan*/  record ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pevent_record*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pevent_event_info (struct trace_seq*,struct event_format*,struct pevent_record*) ; 
 int /*<<< orphan*/  trace_seq_do_printf (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_init (struct trace_seq*) ; 

void event_format__print(struct event_format *event,
			 int cpu, void *data, int size)
{
	struct pevent_record record;
	struct trace_seq s;

	memset(&record, 0, sizeof(record));
	record.cpu = cpu;
	record.size = size;
	record.data = data;

	trace_seq_init(&s);
	pevent_event_info(&s, event, &record);
	trace_seq_do_printf(&s);
}