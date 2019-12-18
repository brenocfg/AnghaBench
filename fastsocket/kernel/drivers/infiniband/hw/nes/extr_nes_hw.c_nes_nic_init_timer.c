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
typedef  int u32 ;
struct nes_hw_tune_timer {scalar_t__ timer_in_use_old; int timer_in_use; scalar_t__ timer_direction_downward; scalar_t__ timer_direction_upward; } ;
struct nes_device {scalar_t__ regs; scalar_t__ deepcq_count; struct nes_adapter* nesadapter; } ;
struct nes_adapter {int /*<<< orphan*/  periodic_timer_lock; struct nes_hw_tune_timer tune_timer; } ;

/* Variables and functions */
 int NES_NIC_FAST_TIMER ; 
 scalar_t__ NES_PERIODIC_CONTROL ; 
 int /*<<< orphan*/  nes_write32 (scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void  nes_nic_init_timer(struct nes_device *nesdev)
{
	unsigned long flags;
	struct nes_adapter *nesadapter = nesdev->nesadapter;
	struct nes_hw_tune_timer *shared_timer = &nesadapter->tune_timer;

	spin_lock_irqsave(&nesadapter->periodic_timer_lock, flags);

	if (shared_timer->timer_in_use_old == 0) {
		nesdev->deepcq_count = 0;
		shared_timer->timer_direction_upward = 0;
		shared_timer->timer_direction_downward = 0;
		shared_timer->timer_in_use = NES_NIC_FAST_TIMER;
		shared_timer->timer_in_use_old = 0;

	}
	if (shared_timer->timer_in_use != shared_timer->timer_in_use_old) {
		shared_timer->timer_in_use_old = shared_timer->timer_in_use;
		nes_write32(nesdev->regs+NES_PERIODIC_CONTROL,
			0x80000000 | ((u32)(shared_timer->timer_in_use*8)));
	}
	/* todo use netdev->mtu to set thresholds */
	spin_unlock_irqrestore(&nesadapter->periodic_timer_lock, flags);
}