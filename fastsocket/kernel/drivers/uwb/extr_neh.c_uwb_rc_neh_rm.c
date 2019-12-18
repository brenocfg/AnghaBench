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
struct uwb_rc_neh {int /*<<< orphan*/  timer; } ;
struct uwb_rc {int /*<<< orphan*/  neh_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __uwb_rc_neh_rm (struct uwb_rc*,struct uwb_rc_neh*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uwb_rc_neh_put (struct uwb_rc_neh*) ; 

void uwb_rc_neh_rm(struct uwb_rc *rc, struct uwb_rc_neh *neh)
{
	unsigned long flags;

	spin_lock_irqsave(&rc->neh_lock, flags);
	__uwb_rc_neh_rm(rc, neh);
	spin_unlock_irqrestore(&rc->neh_lock, flags);

	del_timer_sync(&neh->timer);
	uwb_rc_neh_put(neh);
}