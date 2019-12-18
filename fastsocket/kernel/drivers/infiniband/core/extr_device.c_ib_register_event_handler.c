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
struct ib_event_handler {TYPE_1__* device; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_handler_lock; int /*<<< orphan*/  event_handler_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ib_register_event_handler  (struct ib_event_handler *event_handler)
{
	unsigned long flags;

	spin_lock_irqsave(&event_handler->device->event_handler_lock, flags);
	list_add_tail(&event_handler->list,
		      &event_handler->device->event_handler_list);
	spin_unlock_irqrestore(&event_handler->device->event_handler_lock, flags);

	return 0;
}