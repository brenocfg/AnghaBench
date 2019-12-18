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
struct ocfs2_super {int dummy; } ;
struct ocfs2_lock_res {int l_flags; int /*<<< orphan*/  l_event; int /*<<< orphan*/  l_lock; int /*<<< orphan*/  l_type; int /*<<< orphan*/  l_level; int /*<<< orphan*/  l_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DLM_LOCK_NL ; 
 int OCFS2_LOCK_NOCACHE ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_generic_handle_bast (struct ocfs2_lock_res*,int) ; 
 struct ocfs2_super* ocfs2_get_lockres_osb (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  ocfs2_lock_type_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_schedule_blocked_lock (struct ocfs2_super*,struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  ocfs2_wake_downconvert_thread (struct ocfs2_super*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_blocking_ast(void *opaque, int level)
{
	struct ocfs2_lock_res *lockres = opaque;
	struct ocfs2_super *osb = ocfs2_get_lockres_osb(lockres);
	int needs_downconvert;
	unsigned long flags;

	BUG_ON(level <= DLM_LOCK_NL);

	mlog(0, "BAST fired for lockres %s, blocking %d, level %d type %s\n",
	     lockres->l_name, level, lockres->l_level,
	     ocfs2_lock_type_string(lockres->l_type));

	/*
	 * We can skip the bast for locks which don't enable caching -
	 * they'll be dropped at the earliest possible time anyway.
	 */
	if (lockres->l_flags & OCFS2_LOCK_NOCACHE)
		return;

	spin_lock_irqsave(&lockres->l_lock, flags);
	needs_downconvert = ocfs2_generic_handle_bast(lockres, level);
	if (needs_downconvert)
		ocfs2_schedule_blocked_lock(osb, lockres);
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	wake_up(&lockres->l_event);

	ocfs2_wake_downconvert_thread(osb);
}