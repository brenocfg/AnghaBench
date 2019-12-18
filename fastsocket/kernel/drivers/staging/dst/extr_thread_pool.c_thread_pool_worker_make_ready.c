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
struct thread_pool_worker {int /*<<< orphan*/  worker_entry; scalar_t__ has_data; int /*<<< orphan*/  need_exit; struct thread_pool* pool; } ;
struct thread_pool {int /*<<< orphan*/  thread_lock; int /*<<< orphan*/  thread_num; int /*<<< orphan*/  wait; int /*<<< orphan*/  ready_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_pool_exit_worker (struct thread_pool_worker*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void thread_pool_worker_make_ready(struct thread_pool_worker *w)
{
	struct thread_pool *p = w->pool;

	mutex_lock(&p->thread_lock);

	if (!w->need_exit) {
		list_move_tail(&w->worker_entry, &p->ready_list);
		w->has_data = 0;
		mutex_unlock(&p->thread_lock);

		wake_up(&p->wait);
	} else {
		p->thread_num--;
		list_del(&w->worker_entry);
		mutex_unlock(&p->thread_lock);

		thread_pool_exit_worker(w);
	}
}