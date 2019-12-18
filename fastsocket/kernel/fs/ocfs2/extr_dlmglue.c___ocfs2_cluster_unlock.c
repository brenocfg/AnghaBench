#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_super {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * key; } ;
struct ocfs2_lock_res {TYPE_1__ l_lockdep_map; int /*<<< orphan*/  l_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_exit_void () ; 
 int /*<<< orphan*/  ocfs2_dec_holders (struct ocfs2_lock_res*,int) ; 
 int /*<<< orphan*/  ocfs2_downconvert_on_unlock (struct ocfs2_super*,struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  rwsem_release (TYPE_1__*,int,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void __ocfs2_cluster_unlock(struct ocfs2_super *osb,
				   struct ocfs2_lock_res *lockres,
				   int level,
				   unsigned long caller_ip)
{
	unsigned long flags;

	mlog_entry_void();
	spin_lock_irqsave(&lockres->l_lock, flags);
	ocfs2_dec_holders(lockres, level);
	ocfs2_downconvert_on_unlock(osb, lockres);
	spin_unlock_irqrestore(&lockres->l_lock, flags);
#ifdef CONFIG_DEBUG_LOCK_ALLOC
	if (lockres->l_lockdep_map.key != NULL)
		rwsem_release(&lockres->l_lockdep_map, 1, caller_ip);
#endif
	mlog_exit_void();
}