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

/* Variables and functions */
 unsigned int TRACE_ITER_RECORD_CMD ; 
 int /*<<< orphan*/  trace_event_enable_cmd_record (int) ; 
 unsigned int trace_flags ; 

__attribute__((used)) static void set_tracer_flags(unsigned int mask, int enabled)
{
	/* do nothing if flag is already set */
	if (!!(trace_flags & mask) == !!enabled)
		return;

	if (enabled)
		trace_flags |= mask;
	else
		trace_flags &= ~mask;

	if (mask == TRACE_ITER_RECORD_CMD)
		trace_event_enable_cmd_record(enabled);
}