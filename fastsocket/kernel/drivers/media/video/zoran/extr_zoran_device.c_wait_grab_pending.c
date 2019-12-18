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
struct zoran {scalar_t__ v4l_pend_tail; scalar_t__ v4l_pend_head; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  v4l_capq; int /*<<< orphan*/  v4l_memgrab_active; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zr36057_set_memgrab (struct zoran*,int /*<<< orphan*/ ) ; 

int
wait_grab_pending (struct zoran *zr)
{
	unsigned long flags;

	/* wait until all pending grabs are finished */

	if (!zr->v4l_memgrab_active)
		return 0;

	wait_event_interruptible(zr->v4l_capq,
			(zr->v4l_pend_tail == zr->v4l_pend_head));
	if (signal_pending(current))
		return -ERESTARTSYS;

	spin_lock_irqsave(&zr->spinlock, flags);
	zr36057_set_memgrab(zr, 0);
	spin_unlock_irqrestore(&zr->spinlock, flags);

	return 0;
}