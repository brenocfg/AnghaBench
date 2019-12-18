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
typedef  void* u64 ;
struct wakeup_entry {int /*<<< orphan*/  pid; } ;
struct wake_event {int waker; int /*<<< orphan*/  wakee; struct wake_event* next; void* time; } ;
struct trace_entry {int flags; } ;
struct per_pid {TYPE_1__* current; int /*<<< orphan*/  pid; } ;
struct TYPE_2__ {scalar_t__ state; void* state_since; } ;

/* Variables and functions */
 int TRACE_FLAG_HARDIRQ ; 
 int TRACE_FLAG_SOFTIRQ ; 
 scalar_t__ TYPE_BLOCKED ; 
 scalar_t__ TYPE_NONE ; 
 void* TYPE_WAITING ; 
 struct per_pid* find_create_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_put_sample (int /*<<< orphan*/ ,scalar_t__,int,void*,void*) ; 
 struct wake_event* wake_events ; 
 struct wake_event* zalloc (int) ; 

__attribute__((used)) static void
sched_wakeup(int cpu, u64 timestamp, int pid, struct trace_entry *te)
{
	struct per_pid *p;
	struct wakeup_entry *wake = (void *)te;
	struct wake_event *we = zalloc(sizeof(*we));

	if (!we)
		return;

	we->time = timestamp;
	we->waker = pid;

	if ((te->flags & TRACE_FLAG_HARDIRQ) || (te->flags & TRACE_FLAG_SOFTIRQ))
		we->waker = -1;

	we->wakee = wake->pid;
	we->next = wake_events;
	wake_events = we;
	p = find_create_pid(we->wakee);

	if (p && p->current && p->current->state == TYPE_NONE) {
		p->current->state_since = timestamp;
		p->current->state = TYPE_WAITING;
	}
	if (p && p->current && p->current->state == TYPE_BLOCKED) {
		pid_put_sample(p->pid, p->current->state, cpu, p->current->state_since, timestamp);
		p->current->state_since = timestamp;
		p->current->state = TYPE_WAITING;
	}
}