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
struct TYPE_2__ {scalar_t__ highest_blocked; scalar_t__ type; } ;
struct dlm_lock {TYPE_1__ ml; int /*<<< orphan*/  bast_list; scalar_t__ bast_pending; int /*<<< orphan*/  spinlock; } ;
struct dlm_ctxt {int /*<<< orphan*/  ast_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ LKM_EXMODE ; 
 scalar_t__ LKM_IVMODE ; 
 scalar_t__ LKM_NLMODE ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlm_should_cancel_bast(struct dlm_ctxt *dlm, struct dlm_lock *lock)
{
	assert_spin_locked(&dlm->ast_lock);
	assert_spin_locked(&lock->spinlock);

	if (lock->ml.highest_blocked == LKM_IVMODE)
		return 0;
	BUG_ON(lock->ml.highest_blocked == LKM_NLMODE);

	if (lock->bast_pending &&
	    list_empty(&lock->bast_list))
		/* old bast already sent, ok */
		return 0;

	if (lock->ml.type == LKM_EXMODE)
		/* EX blocks anything left, any bast still valid */
		return 0;
	else if (lock->ml.type == LKM_NLMODE)
		/* NL blocks nothing, no reason to send any bast, cancel it */
		return 1;
	else if (lock->ml.highest_blocked != LKM_EXMODE)
		/* PR only blocks EX */
		return 1;

	return 0;
}