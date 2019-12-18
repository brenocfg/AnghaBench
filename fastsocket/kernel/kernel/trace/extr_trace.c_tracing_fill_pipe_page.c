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
struct TYPE_2__ {size_t len; } ;
struct trace_iterator {int /*<<< orphan*/ * ent; TYPE_1__ seq; } ;

/* Variables and functions */
 int TRACE_TYPE_NO_CONSUME ; 
 int TRACE_TYPE_PARTIAL_LINE ; 
 int /*<<< orphan*/  find_next_entry_inc (struct trace_iterator*) ; 
 int print_trace_line (struct trace_iterator*) ; 
 int /*<<< orphan*/  trace_consume (struct trace_iterator*) ; 

__attribute__((used)) static size_t
tracing_fill_pipe_page(size_t rem, struct trace_iterator *iter)
{
	size_t count;
	int ret;

	/* Seq buffer is page-sized, exactly what we need. */
	for (;;) {
		count = iter->seq.len;
		ret = print_trace_line(iter);
		count = iter->seq.len - count;
		if (rem < count) {
			rem = 0;
			iter->seq.len -= count;
			break;
		}
		if (ret == TRACE_TYPE_PARTIAL_LINE) {
			iter->seq.len -= count;
			break;
		}

		if (ret != TRACE_TYPE_NO_CONSUME)
			trace_consume(iter);
		rem -= count;
		if (!find_next_entry_inc(iter))	{
			rem = 0;
			iter->ent = NULL;
			break;
		}
	}

	return rem;
}