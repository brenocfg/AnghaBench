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
struct utrace_engine_ops {int dummy; } ;
struct utrace_engine {int /*<<< orphan*/  entry; } ;
struct utrace {int pending_attach; int /*<<< orphan*/  lock; int /*<<< orphan*/  attaching; } ;
struct task_struct {scalar_t__ exit_state; scalar_t__ utrace_flags; } ;

/* Variables and functions */
 int EEXIST ; 
 int ESRCH ; 
 scalar_t__ EXIT_DEAD ; 
 int /*<<< orphan*/  REAP ; 
 int UTRACE_ATTACH_EXCLUSIVE ; 
 scalar_t__ UTRACE_EVENT (int /*<<< orphan*/ ) ; 
 int find_matching_engine (struct utrace*,int,struct utrace_engine_ops const*,void*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int utrace_add_engine(struct task_struct *target,
			     struct utrace *utrace,
			     struct utrace_engine *engine,
			     int flags,
			     const struct utrace_engine_ops *ops,
			     void *data)
{
	int ret;

	spin_lock(&utrace->lock);

	ret = -EEXIST;
	if ((flags & UTRACE_ATTACH_EXCLUSIVE) &&
	     unlikely(find_matching_engine(utrace, flags, ops, data)))
		goto unlock;

	/*
	 * In case we had no engines before, make sure that
	 * utrace_flags is not zero. Since we did unlock+lock
	 * at least once after utrace_task_alloc() installed
	 * ->utrace, we have the necessary barrier which pairs
	 * with rmb() in task_utrace_struct().
	 */
	ret = -ESRCH;
	if (!target->utrace_flags) {
		target->utrace_flags = UTRACE_EVENT(REAP);
		/*
		 * If we race with tracehook_prepare_release_task()
		 * make sure that either it sees utrace_flags != 0
		 * or we see exit_state == EXIT_DEAD.
		 */
		smp_mb();
		if (unlikely(target->exit_state == EXIT_DEAD)) {
			target->utrace_flags = 0;
			goto unlock;
		}
	}

	/*
	 * Put the new engine on the pending ->attaching list.
	 * Make sure it gets onto the ->attached list by the next
	 * time it's examined.  Setting ->pending_attach ensures
	 * that start_report() takes the lock and splices the lists
	 * before the next new reporting pass.
	 *
	 * When target == current, it would be safe just to call
	 * splice_attaching() right here.  But if we're inside a
	 * callback, that would mean the new engine also gets
	 * notified about the event that precipitated its own
	 * creation.  This is not what the user wants.
	 */
	list_add_tail(&engine->entry, &utrace->attaching);
	utrace->pending_attach = 1;
	ret = 0;
unlock:
	spin_unlock(&utrace->lock);

	return ret;
}