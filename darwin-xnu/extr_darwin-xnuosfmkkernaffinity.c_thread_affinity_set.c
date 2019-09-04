#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_2__* affinity_space_t ;
typedef  TYPE_3__* affinity_set_t ;
struct TYPE_27__ {TYPE_2__* affinity_space; } ;
struct TYPE_26__ {int /*<<< orphan*/  aset_tag; } ;
struct TYPE_25__ {int /*<<< orphan*/  aspc_lock; } ;
struct TYPE_24__ {TYPE_3__* affinity_set; int /*<<< orphan*/  active; TYPE_7__* task; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,TYPE_1__*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  KERN_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  KERN_TERMINATED ; 
 int /*<<< orphan*/  THREAD_AFFINITY_TAG_NULL ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int /*<<< orphan*/  affinity_set_add (TYPE_3__*,TYPE_1__*) ; 
 TYPE_3__* affinity_set_alloc () ; 
 TYPE_3__* affinity_set_find (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  affinity_set_free (TYPE_3__*) ; 
 int /*<<< orphan*/  affinity_set_place (TYPE_2__*,TYPE_3__*) ; 
 TYPE_3__* affinity_set_remove (TYPE_3__*,TYPE_1__*) ; 
 TYPE_2__* affinity_space_alloc () ; 
 int /*<<< orphan*/  affinity_space_free (TYPE_2__*) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_lock (TYPE_7__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_7__*) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_1__*) ; 

kern_return_t
thread_affinity_set(thread_t thread, uint32_t tag)
{
	affinity_set_t		aset;
	affinity_set_t		empty_aset = NULL;
	affinity_space_t	aspc;
	affinity_space_t	new_aspc = NULL;

	DBG("thread_affinity_set(%p,%u)\n", thread, tag);

	task_lock(thread->task);
	aspc = thread->task->affinity_space;
	if (aspc == NULL) {
		task_unlock(thread->task);
		new_aspc = affinity_space_alloc();
		if (new_aspc == NULL)
			return KERN_RESOURCE_SHORTAGE;
		task_lock(thread->task);
		if (thread->task->affinity_space == NULL) {
			thread->task->affinity_space = new_aspc;
			new_aspc = NULL;
		}
		aspc = thread->task->affinity_space;
	}
	task_unlock(thread->task);
	if (new_aspc)
		affinity_space_free(new_aspc);

	thread_mtx_lock(thread);
	if (!thread->active) {
		/* Beaten to lock and the thread is dead */
		thread_mtx_unlock(thread);
		return KERN_TERMINATED;
	}

	lck_mtx_lock(&aspc->aspc_lock);
	aset = thread->affinity_set;
	if (aset != NULL) {
		/*
		 * Remove thread from current affinity set
		 */
		DBG("thread_affinity_set(%p,%u) removing from aset %p\n",
			thread, tag, aset);
		empty_aset = affinity_set_remove(aset, thread);
	}

	if (tag != THREAD_AFFINITY_TAG_NULL) {
		aset = affinity_set_find(aspc, tag);
		if (aset != NULL) {
			/*
			 * Add thread to existing affinity set
			 */
			DBG("thread_affinity_set(%p,%u) found aset %p\n",
				thread, tag, aset);
		} else {
			/*
			 * Use the new affinity set, add this thread
			 * and place it in a suitable processor set.
			 */
			if (empty_aset != NULL) {
				aset = empty_aset;
				empty_aset = NULL;
			} else {
				aset = affinity_set_alloc();
				if (aset == NULL) {
					lck_mtx_unlock(&aspc->aspc_lock);
					thread_mtx_unlock(thread);
					return KERN_RESOURCE_SHORTAGE;
				}
			}
			DBG("thread_affinity_set(%p,%u) (re-)using aset %p\n",
				thread, tag, aset);
			aset->aset_tag = tag;
			affinity_set_place(aspc, aset);
		}
		affinity_set_add(aset, thread);
	}

	lck_mtx_unlock(&aspc->aspc_lock);
	thread_mtx_unlock(thread);

	/*
	 * If we wound up not using an empty aset we created,
	 * free it here.
	 */
	if (empty_aset != NULL)
		affinity_set_free(empty_aset);

	if (thread == current_thread())
	        thread_block(THREAD_CONTINUE_NULL);

	return KERN_SUCCESS;
}