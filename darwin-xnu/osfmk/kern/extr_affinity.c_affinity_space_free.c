#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct affinity_space {int dummy; } ;
typedef  TYPE_1__* affinity_space_t ;
struct TYPE_5__ {int /*<<< orphan*/  aspc_lock; int /*<<< orphan*/  aspc_affinities; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_lck_grp ; 

__attribute__((used)) static void
affinity_space_free(affinity_space_t aspc)
{
	assert(queue_empty(&aspc->aspc_affinities));

	lck_mtx_destroy(&aspc->aspc_lock, &task_lck_grp);
	DBG("affinity_space_free(%p)\n", aspc);
	kfree(aspc, sizeof(struct affinity_space));
}