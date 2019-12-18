#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct affinity_space {int dummy; } ;
typedef  TYPE_1__* affinity_space_t ;
struct TYPE_4__ {int aspc_task_count; int /*<<< orphan*/  aspc_affinities; int /*<<< orphan*/  aspc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,TYPE_1__*) ; 
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_lck_attr ; 
 int /*<<< orphan*/  task_lck_grp ; 

__attribute__((used)) static affinity_space_t
affinity_space_alloc(void) 
{
	affinity_space_t	aspc;

	aspc = (affinity_space_t) kalloc(sizeof(struct affinity_space));
	if (aspc == NULL)
		return NULL;

	lck_mtx_init(&aspc->aspc_lock, &task_lck_grp, &task_lck_attr);
	queue_init(&aspc->aspc_affinities);
	aspc->aspc_task_count = 1;

	DBG("affinity_space_create() returns %p\n", aspc);
	return aspc;
}