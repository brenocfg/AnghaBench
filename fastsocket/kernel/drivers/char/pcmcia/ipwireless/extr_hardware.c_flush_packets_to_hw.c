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
struct ipw_hardware {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int get_current_packet_priority (struct ipw_hardware*) ; 
 scalar_t__ send_pending_packet (struct ipw_hardware*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void flush_packets_to_hw(struct ipw_hardware *hw)
{
	int priority_limit;
	unsigned long flags;

	spin_lock_irqsave(&hw->lock, flags);
	priority_limit = get_current_packet_priority(hw);
	spin_unlock_irqrestore(&hw->lock, flags);

	while (send_pending_packet(hw, priority_limit));
}