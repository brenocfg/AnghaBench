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
struct user_lock_res {int l_blocking; int /*<<< orphan*/  l_event; int /*<<< orphan*/  l_lock; int /*<<< orphan*/  l_flags; int /*<<< orphan*/  l_name; int /*<<< orphan*/  l_namelen; } ;

/* Variables and functions */
 int /*<<< orphan*/  USER_LOCK_BLOCKED ; 
 int /*<<< orphan*/  __user_dlm_queue_lockres (struct user_lock_res*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void user_bast(void *opaque, int level)
{
	struct user_lock_res *lockres = opaque;

	mlog(0, "Blocking AST fired for lockres %.*s. Blocking level %d\n",
	     lockres->l_namelen, lockres->l_name, level);

	spin_lock(&lockres->l_lock);
	lockres->l_flags |= USER_LOCK_BLOCKED;
	if (level > lockres->l_blocking)
		lockres->l_blocking = level;

	__user_dlm_queue_lockres(lockres);
	spin_unlock(&lockres->l_lock);

	wake_up(&lockres->l_event);
}