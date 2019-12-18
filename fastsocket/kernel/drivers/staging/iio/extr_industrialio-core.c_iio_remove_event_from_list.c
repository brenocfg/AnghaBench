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
struct list_head {int dummy; } ;
struct iio_interrupt {int /*<<< orphan*/  ev_list_lock; } ;
struct iio_event_handler_list {scalar_t__ refcount; int /*<<< orphan*/  exist_lock; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct iio_interrupt* to_iio_interrupt (struct list_head*) ; 

void iio_remove_event_from_list(struct iio_event_handler_list *el,
			       struct list_head *head)
{
	unsigned long flags;
	struct iio_interrupt *inter = to_iio_interrupt(head);

	mutex_lock(&el->exist_lock);
	el->refcount--;
	if (el->refcount == 0) {
		/* Take the event list spin lock */
		spin_lock_irqsave(&inter->ev_list_lock, flags);
		list_del_init(&el->list);
		spin_unlock_irqrestore(&inter->ev_list_lock, flags);
	}
	mutex_unlock(&el->exist_lock);
}