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
struct thread_pool_worker {void (* cleanup ) (void*) ;unsigned int id; void* thread; int /*<<< orphan*/  worker_entry; void* private; int /*<<< orphan*/  wait; struct thread_pool* pool; } ;
struct thread_pool {int /*<<< orphan*/  thread_lock; int /*<<< orphan*/  thread_num; int /*<<< orphan*/  ready_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct thread_pool_worker*) ; 
 void* kthread_run (int /*<<< orphan*/ ,struct thread_pool_worker*,char*,char*) ; 
 int /*<<< orphan*/  kthread_stop (void*) ; 
 struct thread_pool_worker* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_pool_worker_func ; 

int thread_pool_add_worker(struct thread_pool *p,
		char *name,
		unsigned int id,
		void *(* init)(void *private),
		void (* cleanup)(void *private),
		void *private)
{
	struct thread_pool_worker *w;
	int err = -ENOMEM;

	w = kzalloc(sizeof(struct thread_pool_worker), GFP_KERNEL);
	if (!w)
		goto err_out_exit;

	w->pool = p;
	init_waitqueue_head(&w->wait);
	w->cleanup = cleanup;
	w->id = id;

	w->thread = kthread_run(thread_pool_worker_func, w, "%s", name);
	if (IS_ERR(w->thread)) {
		err = PTR_ERR(w->thread);
		goto err_out_free;
	}

	w->private = init(private);
	if (IS_ERR(w->private)) {
		err = PTR_ERR(w->private);
		goto err_out_stop_thread;
	}

	mutex_lock(&p->thread_lock);
	list_add_tail(&w->worker_entry, &p->ready_list);
	p->thread_num++;
	mutex_unlock(&p->thread_lock);

	return 0;

err_out_stop_thread:
	kthread_stop(w->thread);
err_out_free:
	kfree(w);
err_out_exit:
	return err;
}