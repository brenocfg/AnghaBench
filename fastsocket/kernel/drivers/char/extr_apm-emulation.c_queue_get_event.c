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
struct apm_queue {int event_tail; int /*<<< orphan*/ * events; } ;
typedef  int /*<<< orphan*/  apm_event_t ;

/* Variables and functions */
 int APM_MAX_EVENTS ; 

__attribute__((used)) static inline apm_event_t queue_get_event(struct apm_queue *q)
{
	q->event_tail = (q->event_tail + 1) % APM_MAX_EVENTS;
	return q->events[q->event_tail];
}