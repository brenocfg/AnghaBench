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
typedef  int /*<<< orphan*/  u32 ;
struct lbs_private {scalar_t__ psstate; int /*<<< orphan*/  driver_lock; int /*<<< orphan*/  waitq; int /*<<< orphan*/  event_fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBS_DEB_THREAD ; 
 scalar_t__ PS_STATE_AWAKE ; 
 scalar_t__ PS_STATE_SLEEP ; 
 int /*<<< orphan*/  __kfifo_put (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void lbs_queue_event(struct lbs_private *priv, u32 event)
{
	unsigned long flags;

	lbs_deb_enter(LBS_DEB_THREAD);
	spin_lock_irqsave(&priv->driver_lock, flags);

	if (priv->psstate == PS_STATE_SLEEP)
		priv->psstate = PS_STATE_AWAKE;

	__kfifo_put(priv->event_fifo, (unsigned char *) &event, sizeof(u32));

	wake_up_interruptible(&priv->waitq);

	spin_unlock_irqrestore(&priv->driver_lock, flags);
	lbs_deb_leave(LBS_DEB_THREAD);
}