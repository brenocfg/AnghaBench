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
struct thread_info {int /*<<< orphan*/  thumbee_state; } ;
struct notifier_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  thumbee_state; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
#define  THREAD_NOTIFY_FLUSH 129 
#define  THREAD_NOTIFY_SWITCH 128 
 TYPE_1__* current_thread_info () ; 
 int /*<<< orphan*/  teehbr_read () ; 
 int /*<<< orphan*/  teehbr_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int thumbee_notifier(struct notifier_block *self, unsigned long cmd, void *t)
{
	struct thread_info *thread = t;

	switch (cmd) {
	case THREAD_NOTIFY_FLUSH:
		thread->thumbee_state = 0;
		break;
	case THREAD_NOTIFY_SWITCH:
		current_thread_info()->thumbee_state = teehbr_read();
		teehbr_write(thread->thumbee_state);
		break;
	}

	return NOTIFY_DONE;
}