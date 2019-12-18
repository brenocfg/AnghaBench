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
struct nouveau_eventh {int /*<<< orphan*/  head; } ;
struct nouveau_event {int index_nr; int /*<<< orphan*/  lock; scalar_t__ toggle_lock; TYPE_1__* index; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_event_enable_locked (struct nouveau_event*,int) ; 
 int /*<<< orphan*/  spin_lock (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (scalar_t__) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
nouveau_event_get(struct nouveau_event *event, int index,
		  struct nouveau_eventh *handler)
{
	unsigned long flags;

	if (index >= event->index_nr)
		return;

	spin_lock_irqsave(&event->lock, flags);
	list_add(&handler->head, &event->index[index].list);
	if (event->toggle_lock)
		spin_lock(event->toggle_lock);
	nouveau_event_enable_locked(event, index);
	if (event->toggle_lock)
		spin_unlock(event->toggle_lock);
	spin_unlock_irqrestore(&event->lock, flags);
}