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
struct usb_hub {int /*<<< orphan*/  event_list; int /*<<< orphan*/  disconnected; int /*<<< orphan*/  intfdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  pm_usage_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hub_event_list ; 
 int /*<<< orphan*/  hub_event_lock ; 
 int /*<<< orphan*/  khubd_wait ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* to_usb_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kick_khubd(struct usb_hub *hub)
{
	unsigned long	flags;

	/* Suppress autosuspend until khubd runs */
	atomic_set(&to_usb_interface(hub->intfdev)->pm_usage_cnt, 1);

	spin_lock_irqsave(&hub_event_lock, flags);
	if (!hub->disconnected && list_empty(&hub->event_list)) {
		list_add_tail(&hub->event_list, &hub_event_list);
		wake_up(&khubd_wait);
	}
	spin_unlock_irqrestore(&hub_event_lock, flags);
}