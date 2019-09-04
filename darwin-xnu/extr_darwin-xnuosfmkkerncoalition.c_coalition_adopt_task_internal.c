#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
typedef  scalar_t__ kern_return_t ;
typedef  TYPE_2__* coalition_t ;
struct TYPE_12__ {size_t type; int /*<<< orphan*/  id; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  active_count; scalar_t__ terminated; scalar_t__ reaped; } ;
struct TYPE_11__ {TYPE_2__** coalition; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MACH_COALITION ; 
 int /*<<< orphan*/  KDBG_RELEASE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ KERN_ALREADY_IN_SET ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ KERN_TERMINATED ; 
 int /*<<< orphan*/  MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_COALITION_ADOPT ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  adopt_task ; 
 int /*<<< orphan*/  cid ; 
 scalar_t__ coal_call (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  coal_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  coal_type_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coalition_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  coalition_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  ct ; 
 scalar_t__ get_task_uniqueid (TYPE_1__*) ; 
 int /*<<< orphan*/  rc ; 
 int /*<<< orphan*/  task_pid (TYPE_1__*) ; 

__attribute__((used)) static kern_return_t
coalition_adopt_task_internal(coalition_t coal, task_t task)
{
	kern_return_t kr;

	if (task->coalition[coal->type]) {
		return KERN_ALREADY_IN_SET;
	}

	coalition_lock(coal);

	if (coal->reaped || coal->terminated) {
		coalition_unlock(coal);
		return KERN_TERMINATED;
	}

	kr = coal_call(coal, adopt_task, task);
	if (kr != KERN_SUCCESS)
		goto out_unlock;

	coal->active_count++;

	coal->ref_count++;

	task->coalition[coal->type] = coal;

out_unlock:
#if COALITION_DEBUG
	(void)coal; /* need expression after label */
	uint64_t cid = coal->id;
	uint32_t rc = coal->ref_count;
	uint32_t ct = coal->type;
#endif
	if (get_task_uniqueid(task) != UINT64_MAX) {
		/* On 32-bit targets, uniqueid will get truncated to 32 bits */
		KDBG_RELEASE(MACHDBG_CODE(DBG_MACH_COALITION, MACH_COALITION_ADOPT),
			coal->id, get_task_uniqueid(task));
	}

	coalition_unlock(coal);

	coal_dbg("task:%d, id:%llu type:%s ref_count:%u, kr=%d",
		 task_pid(task), cid, coal_type_str(ct), rc, kr);
	return kr;
}