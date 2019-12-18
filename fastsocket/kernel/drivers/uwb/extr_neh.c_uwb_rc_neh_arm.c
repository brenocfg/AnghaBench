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
struct uwb_rc_neh {int /*<<< orphan*/  timer; scalar_t__ context; } ;
struct uwb_rc {int /*<<< orphan*/  neh_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  UWB_RC_CMD_TIMEOUT_MS ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void uwb_rc_neh_arm(struct uwb_rc *rc, struct uwb_rc_neh *neh)
{
	unsigned long flags;

	spin_lock_irqsave(&rc->neh_lock, flags);
	if (neh->context)
		mod_timer(&neh->timer,
			  jiffies + msecs_to_jiffies(UWB_RC_CMD_TIMEOUT_MS));
	spin_unlock_irqrestore(&rc->neh_lock, flags);
}