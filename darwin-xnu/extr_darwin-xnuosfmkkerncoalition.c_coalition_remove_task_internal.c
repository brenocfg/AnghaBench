#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_2__* coalition_t ;
struct TYPE_11__ {scalar_t__ type; int /*<<< orphan*/  id; } ;
struct TYPE_10__ {TYPE_2__** coalition; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MACH_COALITION ; 
 int /*<<< orphan*/  KDBG_RELEASE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_COALITION_REMOVE ; 
 int /*<<< orphan*/  ac ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cid ; 
 int /*<<< orphan*/  coal_call (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  coal_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coal_type_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coalition_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  coalition_remove_active (TYPE_2__*) ; 
 int /*<<< orphan*/  coalition_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  ct ; 
 int /*<<< orphan*/  get_task_uniqueid (TYPE_1__*) ; 
 int /*<<< orphan*/  rc ; 
 int /*<<< orphan*/  remove_task ; 

__attribute__((used)) static kern_return_t
coalition_remove_task_internal(task_t task, int type)
{
	kern_return_t kr;

	coalition_t coal = task->coalition[type];

	if (!coal)
		return KERN_SUCCESS;

	assert(coal->type == (uint32_t)type);

	coalition_lock(coal);

	kr = coal_call(coal, remove_task, task);

#if COALITION_DEBUG
	uint64_t cid = coal->id;
	uint32_t rc = coal->ref_count;
	int      ac = coal->active_count;
	int      ct = coal->type;
#endif
	KDBG_RELEASE(MACHDBG_CODE(DBG_MACH_COALITION, MACH_COALITION_REMOVE),
		coal->id, get_task_uniqueid(task));
	coalition_unlock(coal);

	coal_dbg("id:%llu type:%s ref_count:%u, active_count:%u, kr=%d",
		 cid, coal_type_str(ct), rc, ac, kr);

	coalition_remove_active(coal);

	return kr;
}