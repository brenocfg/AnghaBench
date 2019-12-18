#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  signal; } ;
struct task_struct {TYPE_2__ pending; scalar_t__ exit_state; TYPE_1__* signal; } ;
struct TYPE_3__ {scalar_t__ group_stop_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGKILL ; 
 struct task_struct* next_thread (struct task_struct*) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_wake_up (struct task_struct*,int) ; 

void zap_other_threads(struct task_struct *p)
{
	struct task_struct *t;

	p->signal->group_stop_count = 0;

	for (t = next_thread(p); t != p; t = next_thread(t)) {
		/*
		 * Don't bother with already dead threads
		 */
		if (t->exit_state)
			continue;

		/* SIGKILL will be handled before any pending SIGSTOP */
		sigaddset(&t->pending.signal, SIGKILL);
		signal_wake_up(t, 1);
	}
}