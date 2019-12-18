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
struct vt_event_wait {int /*<<< orphan*/  list; scalar_t__ done; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vt_event_lock ; 
 int /*<<< orphan*/  vt_event_waitqueue ; 
 int /*<<< orphan*/  vt_events ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void vt_event_wait(struct vt_event_wait *vw)
{
	unsigned long flags;
	/* Prepare the event */
	INIT_LIST_HEAD(&vw->list);
	vw->done = 0;
	/* Queue our event */
	spin_lock_irqsave(&vt_event_lock, flags);
	list_add(&vw->list, &vt_events);
	spin_unlock_irqrestore(&vt_event_lock, flags);
	/* Wait for it to pass */
	wait_event_interruptible(vt_event_waitqueue, vw->done);
	/* Dequeue it */
	spin_lock_irqsave(&vt_event_lock, flags);
	list_del(&vw->list);
	spin_unlock_irqrestore(&vt_event_lock, flags);
}