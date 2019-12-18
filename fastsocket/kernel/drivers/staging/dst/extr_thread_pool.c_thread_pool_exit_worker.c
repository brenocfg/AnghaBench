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
struct thread_pool_worker {int /*<<< orphan*/  private; int /*<<< orphan*/  (* cleanup ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct thread_pool_worker*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void thread_pool_exit_worker(struct thread_pool_worker *w)
{
	kthread_stop(w->thread);

	w->cleanup(w->private);
	kfree(w);
}