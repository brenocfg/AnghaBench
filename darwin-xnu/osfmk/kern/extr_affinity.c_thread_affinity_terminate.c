#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* affinity_space_t ;
typedef  TYPE_3__* affinity_set_t ;
struct TYPE_11__ {TYPE_2__* aset_space; } ;
struct TYPE_10__ {int /*<<< orphan*/  aspc_lock; } ;
struct TYPE_9__ {TYPE_3__* affinity_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  affinity_set_free (TYPE_3__*) ; 
 scalar_t__ affinity_set_remove (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

void
thread_affinity_terminate(thread_t thread)
{
	affinity_set_t		aset = thread->affinity_set;
	affinity_space_t	aspc;

	DBG("thread_affinity_terminate(%p)\n", thread);

	aspc = aset->aset_space;
	lck_mtx_lock(&aspc->aspc_lock);
	if (affinity_set_remove(aset, thread)) {
		affinity_set_free(aset);
	}
	lck_mtx_unlock(&aspc->aspc_lock);
}