#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * extra; } ;
struct thread_info {TYPE_2__ cpu_context; } ;
struct notifier_block {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  extra; } ;
struct TYPE_6__ {TYPE_1__ cpu_context; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
#define  THREAD_NOTIFY_FLUSH 129 
#define  THREAD_NOTIFY_SWITCH 128 
 TYPE_3__* current_thread_info () ; 
 int /*<<< orphan*/  dsp_load_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsp_save_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsp_do(struct notifier_block *self, unsigned long cmd, void *t)
{
	struct thread_info *thread = t;

	switch (cmd) {
	case THREAD_NOTIFY_FLUSH:
		thread->cpu_context.extra[0] = 0;
		thread->cpu_context.extra[1] = 0;
		break;

	case THREAD_NOTIFY_SWITCH:
		dsp_save_state(current_thread_info()->cpu_context.extra);
		dsp_load_state(thread->cpu_context.extra);
		break;
	}

	return NOTIFY_DONE;
}