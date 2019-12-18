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
struct ring_buffer_event {int dummy; } ;
struct ring_buffer {int dummy; } ;
struct ftrace_event_call {int flags; int /*<<< orphan*/  filter; } ;

/* Variables and functions */
 int TRACE_EVENT_FL_FILTERED ; 
 int /*<<< orphan*/  filter_match_preds (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ring_buffer_discard_commit (struct ring_buffer*,struct ring_buffer_event*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int
filter_check_discard(struct ftrace_event_call *call, void *rec,
		     struct ring_buffer *buffer,
		     struct ring_buffer_event *event)
{
	if (unlikely(call->flags & TRACE_EVENT_FL_FILTERED) &&
	    !filter_match_preds(call->filter, rec)) {
		ring_buffer_discard_commit(buffer, event);
		return 1;
	}

	return 0;
}