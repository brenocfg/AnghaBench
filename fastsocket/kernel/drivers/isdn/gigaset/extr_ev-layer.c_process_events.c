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
struct event_t {int /*<<< orphan*/ * ptr; } ;
struct cardstate {unsigned int ev_head; unsigned int ev_tail; scalar_t__ cur_at_seq; int /*<<< orphan*/  dev; int /*<<< orphan*/  ev_lock; struct event_t* events; int /*<<< orphan*/  commands_pending; } ;

/* Variables and functions */
 int MAX_EVENTS ; 
 scalar_t__ SEQ_NONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_command_flags (struct cardstate*) ; 
 int /*<<< orphan*/  process_event (struct cardstate*,struct event_t*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void process_events(struct cardstate *cs)
{
	struct event_t *ev;
	unsigned head, tail;
	int i;
	int check_flags = 0;
	int was_busy;
	unsigned long flags;

	spin_lock_irqsave(&cs->ev_lock, flags);
	head = cs->ev_head;

	for (i = 0; i < 2 * MAX_EVENTS; ++i) {
		tail = cs->ev_tail;
		if (tail == head) {
			if (!check_flags && !cs->commands_pending)
				break;
			check_flags = 0;
			spin_unlock_irqrestore(&cs->ev_lock, flags);
			process_command_flags(cs);
			spin_lock_irqsave(&cs->ev_lock, flags);
			tail = cs->ev_tail;
			if (tail == head) {
				if (!cs->commands_pending)
					break;
				continue;
			}
		}

		ev = cs->events + head;
		was_busy = cs->cur_at_seq != SEQ_NONE;
		spin_unlock_irqrestore(&cs->ev_lock, flags);
		process_event(cs, ev);
		spin_lock_irqsave(&cs->ev_lock, flags);
		kfree(ev->ptr);
		ev->ptr = NULL;
		if (was_busy && cs->cur_at_seq == SEQ_NONE)
			check_flags = 1;

		head = (head + 1) % MAX_EVENTS;
		cs->ev_head = head;
	}

	spin_unlock_irqrestore(&cs->ev_lock, flags);

	if (i == 2 * MAX_EVENTS) {
		dev_err(cs->dev,
			"infinite loop in process_events; aborting.\n");
	}
}