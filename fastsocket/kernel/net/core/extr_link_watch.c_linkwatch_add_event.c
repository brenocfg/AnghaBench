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
struct net_device {struct net_device* link_watch_next; } ;

/* Variables and functions */
 struct net_device* lweventlist ; 
 int /*<<< orphan*/  lweventlist_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void linkwatch_add_event(struct net_device *dev)
{
	unsigned long flags;

	spin_lock_irqsave(&lweventlist_lock, flags);
	dev->link_watch_next = lweventlist;
	lweventlist = dev;
	spin_unlock_irqrestore(&lweventlist_lock, flags);
}