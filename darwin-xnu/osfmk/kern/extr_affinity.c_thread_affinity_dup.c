#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_t ;
typedef  TYPE_3__* affinity_space_t ;
typedef  TYPE_4__* affinity_set_t ;
struct TYPE_17__ {TYPE_3__* aset_space; } ;
struct TYPE_16__ {int /*<<< orphan*/  aspc_lock; } ;
struct TYPE_15__ {TYPE_1__* task; TYPE_4__* affinity_set; } ;
struct TYPE_14__ {TYPE_3__* affinity_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,TYPE_2__*,TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  affinity_set_add (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_2__*) ; 

void
thread_affinity_dup(thread_t parent, thread_t child)
{
	affinity_set_t			aset;
	affinity_space_t		aspc;

	thread_mtx_lock(parent);
	aset = parent->affinity_set;
	DBG("thread_affinity_dup(%p,%p) aset %p\n", parent, child, aset);
	if (aset == NULL) {
		thread_mtx_unlock(parent);
		return;
	}

	aspc = aset->aset_space;
	assert(aspc == parent->task->affinity_space);
	assert(aspc == child->task->affinity_space);

	lck_mtx_lock(&aspc->aspc_lock);
	affinity_set_add(aset, child);
	lck_mtx_unlock(&aspc->aspc_lock);

	thread_mtx_unlock(parent);
}