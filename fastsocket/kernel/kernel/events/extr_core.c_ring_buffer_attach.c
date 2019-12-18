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
struct ring_buffer {int /*<<< orphan*/  event_lock; int /*<<< orphan*/  event_list; } ;
struct perf_event {int /*<<< orphan*/  rb_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ring_buffer_attach(struct perf_event *event,
			       struct ring_buffer *rb)
{
	unsigned long flags;

	if (!list_empty(&event->rb_entry))
		return;

	spin_lock_irqsave(&rb->event_lock, flags);
	if (!list_empty(&event->rb_entry))
		goto unlock;

	list_add(&event->rb_entry, &rb->event_list);
unlock:
	spin_unlock_irqrestore(&rb->event_lock, flags);
}