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
struct ixgbe_adapter {int flags; int timer_event_accumulator; int /*<<< orphan*/  service_timer; int /*<<< orphan*/  num_vfs; } ;

/* Variables and functions */
 int HZ ; 
 int IXGBE_FLAG_NEED_LINK_UPDATE ; 
 int /*<<< orphan*/  ixgbe_check_for_bad_vf (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_service_event_schedule (struct ixgbe_adapter*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void ixgbe_service_timer(unsigned long data)
{
	struct ixgbe_adapter *adapter = (struct ixgbe_adapter *)data;
	unsigned long next_event_offset;
	bool ready = true;

	/* poll faster when waiting for link */
	if (adapter->flags & IXGBE_FLAG_NEED_LINK_UPDATE)
		next_event_offset = HZ / 10;
	else
		next_event_offset = HZ * 2;

#ifdef CONFIG_PCI_IOV
	/*
	 * don't bother with SR-IOV VF DMA hang check if there are
	 * no VFs or the link is down
	 */
	if (!adapter->num_vfs ||
	    (adapter->flags & IXGBE_FLAG_NEED_LINK_UPDATE))
		goto normal_timer_service;

	/* If we have VFs allocated then we must check for DMA hangs */
	ixgbe_check_for_bad_vf(adapter);
	next_event_offset = HZ / 50;
	adapter->timer_event_accumulator++;

	if (adapter->timer_event_accumulator >= 100)
		adapter->timer_event_accumulator = 0;
	else
		ready = false;

normal_timer_service:
#endif
	/* Reset the timer */
	mod_timer(&adapter->service_timer, next_event_offset + jiffies);

	if (ready)
		ixgbe_service_event_schedule(adapter);
}