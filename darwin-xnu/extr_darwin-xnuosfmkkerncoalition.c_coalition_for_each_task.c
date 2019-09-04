#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* coalition_t ;
struct TYPE_11__ {int /*<<< orphan*/  active_count; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 TYPE_1__* COALITION_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  coal_call (TYPE_1__*,int /*<<< orphan*/ ,void*,void (*) (TYPE_1__*,void*,task_t)) ; 
 int /*<<< orphan*/  coal_dbg (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coal_type_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coalition_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  coalition_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  iterate_tasks ; 

void coalition_for_each_task(coalition_t coal, void *ctx,
			     void (*callback)(coalition_t, void *, task_t))
{
	assert(coal != COALITION_NULL);

	coal_dbg("iterating tasks in coalition %p id:%llu type:%s, active_count:%u",
		 coal, coal->id, coal_type_str(coal->type), coal->active_count);

	coalition_lock(coal);

	coal_call(coal, iterate_tasks, ctx, callback);

	coalition_unlock(coal);
}