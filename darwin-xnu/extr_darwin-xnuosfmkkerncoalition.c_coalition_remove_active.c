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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  TYPE_1__* coalition_t ;
typedef  void* boolean_t ;
struct TYPE_5__ {scalar_t__ active_count; int /*<<< orphan*/  id; void* notified; void* terminated; scalar_t__ termrequested; int /*<<< orphan*/  reaped; } ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  ac ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cid ; 
 int /*<<< orphan*/  coal_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  coal_type_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coalition_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  coalition_notify_user (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  coalition_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ct ; 
 int /*<<< orphan*/  rc ; 

void
coalition_remove_active(coalition_t coal)
{
	coalition_lock(coal);

	assert(!coal->reaped);
	assert(coal->active_count > 0);

	coal->active_count--;

	boolean_t do_notify = FALSE;
	uint64_t notify_id = 0;
	uint32_t notify_flags = 0;
	if (coal->termrequested && coal->active_count == 0) {
		/* We only notify once, when active_count reaches zero.
		 * We just decremented, so if it reached zero, we mustn't have
		 * notified already.
		 */
		assert(!coal->terminated);
		coal->terminated = TRUE;

		assert(!coal->notified);

		coal->notified = TRUE;
#if DEVELOPMENT || DEBUG
		do_notify = coal->should_notify;
#else
		do_notify = TRUE;
#endif
		notify_id = coal->id;
		notify_flags = 0;
	}

#if COALITION_DEBUG
	uint64_t cid = coal->id;
	uint32_t rc = coal->ref_count;
	int      ac = coal->active_count;
	int      ct = coal->type;
#endif
	coalition_unlock(coal);

	coal_dbg("id:%llu type:%s ref_count:%u, active_count:%u,%s",
		 cid, coal_type_str(ct), rc, ac, do_notify ? " NOTIFY" : " ");

	if (do_notify) {
		coalition_notify_user(notify_id, notify_flags);
	}
}