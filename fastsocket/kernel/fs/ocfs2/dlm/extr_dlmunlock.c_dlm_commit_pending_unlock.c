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
struct dlm_lock_resource {int dummy; } ;
struct dlm_lock {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

void dlm_commit_pending_unlock(struct dlm_lock_resource *res,
			       struct dlm_lock *lock)
{
	/* leave DLM_LKSB_PUT_LVB on the lksb so any final
	 * update of the lvb will be sent to the new master */
	list_del_init(&lock->list);
}