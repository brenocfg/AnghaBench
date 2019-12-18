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
struct net_device {int flags; int /*<<< orphan*/  state; struct net_device* link_watch_next; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int IFF_UP ; 
 int /*<<< orphan*/  LW_URGENT ; 
 int /*<<< orphan*/  __LINK_STATE_LINKWATCH_PENDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_activate (struct net_device*) ; 
 int /*<<< orphan*/  dev_deactivate (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  linkwatch_add_event (struct net_device*) ; 
 int /*<<< orphan*/  linkwatch_flags ; 
 scalar_t__ linkwatch_nextevent ; 
 int /*<<< orphan*/  linkwatch_schedule_work (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkwatch_urgent_event (struct net_device*) ; 
 struct net_device* lweventlist ; 
 int /*<<< orphan*/  lweventlist_lock ; 
 int /*<<< orphan*/  netdev_state_change (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  rfc2863_policy (struct net_device*) ; 
 int /*<<< orphan*/  smp_mb__before_clear_bit () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void __linkwatch_run_queue(int urgent_only)
{
	struct net_device *next;

	/*
	 * Limit the number of linkwatch events to one
	 * per second so that a runaway driver does not
	 * cause a storm of messages on the netlink
	 * socket.  This limit does not apply to up events
	 * while the device qdisc is down.
	 */
	if (!urgent_only)
		linkwatch_nextevent = jiffies + HZ;
	/* Limit wrap-around effect on delay. */
	else if (time_after(linkwatch_nextevent, jiffies + HZ))
		linkwatch_nextevent = jiffies;

	clear_bit(LW_URGENT, &linkwatch_flags);

	spin_lock_irq(&lweventlist_lock);
	next = lweventlist;
	lweventlist = NULL;
	spin_unlock_irq(&lweventlist_lock);

	while (next) {
		struct net_device *dev = next;

		next = dev->link_watch_next;

		if (urgent_only && !linkwatch_urgent_event(dev)) {
			linkwatch_add_event(dev);
			continue;
		}

		/*
		 * Make sure the above read is complete since it can be
		 * rewritten as soon as we clear the bit below.
		 */
		smp_mb__before_clear_bit();

		/* We are about to handle this device,
		 * so new events can be accepted
		 */
		clear_bit(__LINK_STATE_LINKWATCH_PENDING, &dev->state);

		rfc2863_policy(dev);
		if (dev->flags & IFF_UP) {
			if (netif_carrier_ok(dev))
				dev_activate(dev);
			else
				dev_deactivate(dev);

			netdev_state_change(dev);
		}

		dev_put(dev);
	}

	if (lweventlist)
		linkwatch_schedule_work(0);
}