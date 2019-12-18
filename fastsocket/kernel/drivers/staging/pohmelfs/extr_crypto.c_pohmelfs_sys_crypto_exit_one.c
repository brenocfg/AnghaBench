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
struct pohmelfs_sb {int /*<<< orphan*/  crypto_thread_lock; int /*<<< orphan*/  crypto_thread_num; } ;
struct pohmelfs_crypto_thread {int /*<<< orphan*/  eng; int /*<<< orphan*/  thread_entry; scalar_t__ thread; struct pohmelfs_sb* psb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pohmelfs_crypto_thread*) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pohmelfs_crypto_engine_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pohmelfs_crypto_pages_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pohmelfs_sys_crypto_exit_one(struct pohmelfs_crypto_thread *t)
{
	struct pohmelfs_sb *psb = t->psb;

	if (t->thread)
		kthread_stop(t->thread);

	mutex_lock(&psb->crypto_thread_lock);
	list_del(&t->thread_entry);
	psb->crypto_thread_num--;
	mutex_unlock(&psb->crypto_thread_lock);

	pohmelfs_crypto_engine_exit(&t->eng);
	pohmelfs_crypto_pages_free(&t->eng);
	kfree(t);
}