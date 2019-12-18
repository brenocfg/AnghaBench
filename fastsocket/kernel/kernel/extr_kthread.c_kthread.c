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
struct kthread_create_info {int (* threadfn ) (void*) ;int /*<<< orphan*/  done; TYPE_1__* result; void* data; } ;
struct kthread {scalar_t__ should_stop; int /*<<< orphan*/  exited; } ;
struct TYPE_2__ {int /*<<< orphan*/ * vfork_done; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  do_exit (int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 

__attribute__((used)) static int kthread(void *_create)
{
	/* Copy data: it's on kthread's stack */
	struct kthread_create_info *create = _create;
	int (*threadfn)(void *data) = create->threadfn;
	void *data = create->data;
	struct kthread self;
	int ret;

	self.should_stop = 0;
	init_completion(&self.exited);
	current->vfork_done = &self.exited;

	/* OK, tell user we're spawned, wait for stop or wakeup */
	__set_current_state(TASK_UNINTERRUPTIBLE);
	create->result = current;
	complete(&create->done);
	schedule();

	ret = -EINTR;
	if (!self.should_stop)
		ret = threadfn(data);

	/* we can't just return, we must preserve "self" on stack */
	do_exit(ret);
}