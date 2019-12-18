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
struct nouveau_eventh {int /*<<< orphan*/  head; } ;
struct nouveau_event {int index_nr; int /*<<< orphan*/  lock; scalar_t__ toggle_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_event_disable_locked (struct nouveau_event*,int,int) ; 
 int /*<<< orphan*/  spin_lock (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (scalar_t__) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
nouveau_event_put(struct nouveau_event *event, int index,
		  struct nouveau_eventh *handler)
{
	unsigned long flags;

	if (index >= event->index_nr)
		return;

	spin_lock_irqsave(&event->lock, flags);
	list_del(&handler->head);

	if (event->toggle_lock)
		spin_lock(event->toggle_lock);
	nouveau_event_disable_locked(event, index, 1);
	if (event->toggle_lock)
		spin_unlock(event->toggle_lock);

	spin_unlock_irqrestore(&event->lock, flags);
}