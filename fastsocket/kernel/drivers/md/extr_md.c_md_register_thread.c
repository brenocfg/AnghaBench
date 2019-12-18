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
struct mddev {int dummy; } ;
struct md_thread {void (* run ) (struct md_thread*) ;int /*<<< orphan*/  tsk; struct mddev* mddev; int /*<<< orphan*/  timeout; int /*<<< orphan*/  wqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct md_thread*) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct md_thread*,char*,int /*<<< orphan*/ ,char const*) ; 
 struct md_thread* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_thread ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 

struct md_thread *md_register_thread(void (*run) (struct md_thread *),
		struct mddev *mddev, const char *name)
{
	struct md_thread *thread;

	thread = kzalloc(sizeof(struct md_thread), GFP_KERNEL);
	if (!thread)
		return NULL;

	init_waitqueue_head(&thread->wqueue);

	thread->run = run;
	thread->mddev = mddev;
	thread->timeout = MAX_SCHEDULE_TIMEOUT;
	thread->tsk = kthread_run(md_thread, thread,
				  "%s_%s",
				  mdname(thread->mddev),
				  name);
	if (IS_ERR(thread->tsk)) {
		kfree(thread);
		return NULL;
	}
	return thread;
}