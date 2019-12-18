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
struct workqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WORKQ_THREADREQ_CREATOR_SYNC_UPDATE ; 
 int /*<<< orphan*/  workq_lock_spin (struct workqueue*) ; 
 int /*<<< orphan*/  workq_schedule_creator (int /*<<< orphan*/ *,struct workqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workq_unlock (struct workqueue*) ; 

void
workq_schedule_creator_turnstile_redrive(struct workqueue *wq, bool locked)
{
	if (!locked) workq_lock_spin(wq);
	workq_schedule_creator(NULL, wq, WORKQ_THREADREQ_CREATOR_SYNC_UPDATE);
	if (!locked) workq_unlock(wq);
}