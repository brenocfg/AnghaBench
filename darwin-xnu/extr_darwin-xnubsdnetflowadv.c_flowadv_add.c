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
struct flowadv_fclist {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_CONCAT (struct flowadv_fclist*,struct flowadv_fclist*) ; 
 scalar_t__ STAILQ_EMPTY (struct flowadv_fclist*) ; 
 scalar_t__ THREAD_NULL ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  fadv_active ; 
 struct flowadv_fclist fadv_list ; 
 int /*<<< orphan*/  fadv_lock ; 
 scalar_t__ fadv_thread ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup_one (int /*<<< orphan*/ ) ; 

void
flowadv_add(struct flowadv_fclist *fcl)
{
	if (STAILQ_EMPTY(fcl))
		return;

	lck_mtx_lock_spin(&fadv_lock);

	STAILQ_CONCAT(&fadv_list, fcl);
	VERIFY(!STAILQ_EMPTY(&fadv_list));

	if (!fadv_active && fadv_thread != THREAD_NULL)
		wakeup_one((caddr_t)&fadv_list);

	lck_mtx_unlock(&fadv_lock);
}