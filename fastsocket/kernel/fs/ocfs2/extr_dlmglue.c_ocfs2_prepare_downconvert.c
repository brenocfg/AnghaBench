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
struct ocfs2_lock_res {scalar_t__ l_blocking; int l_level; int l_requested; int /*<<< orphan*/  l_action; int /*<<< orphan*/  l_name; int /*<<< orphan*/  l_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DLM_LOCK_NL ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  OCFS2_AST_DOWNCONVERT ; 
 int /*<<< orphan*/  OCFS2_LOCK_BUSY ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockres_or_flags (struct ocfs2_lock_res*,int /*<<< orphan*/ ) ; 
 unsigned int lockres_set_pending (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,int,...) ; 

__attribute__((used)) static unsigned int ocfs2_prepare_downconvert(struct ocfs2_lock_res *lockres,
					      int new_level)
{
	assert_spin_locked(&lockres->l_lock);

	BUG_ON(lockres->l_blocking <= DLM_LOCK_NL);

	if (lockres->l_level <= new_level) {
		mlog(ML_ERROR, "lockres->l_level (%d) <= new_level (%d)\n",
		     lockres->l_level, new_level);
		BUG();
	}

	mlog(0, "lock %s, new_level = %d, l_blocking = %d\n",
	     lockres->l_name, new_level, lockres->l_blocking);

	lockres->l_action = OCFS2_AST_DOWNCONVERT;
	lockres->l_requested = new_level;
	lockres_or_flags(lockres, OCFS2_LOCK_BUSY);
	return lockres_set_pending(lockres);
}