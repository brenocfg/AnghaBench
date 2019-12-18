#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int testing_irq; int irq_occurred; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ MGSLPC_INFO ;

/* Variables and functions */
 scalar_t__ CHA ; 
 int /*<<< orphan*/  CMD_START_TIMER ; 
 int /*<<< orphan*/  IRQ_TIMER ; 
 scalar_t__ TIMR ; 
 int /*<<< orphan*/  hdlc_mode (TYPE_1__*) ; 
 int /*<<< orphan*/  irq_enable (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  issue_command (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  reset_device (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_reg (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool irq_test(MGSLPC_INFO *info)
{
	unsigned long end_time;
	unsigned long flags;

	spin_lock_irqsave(&info->lock,flags);
	reset_device(info);

	info->testing_irq = true;
	hdlc_mode(info);

	info->irq_occurred = false;

	/* init hdlc mode */

	irq_enable(info, CHA, IRQ_TIMER);
	write_reg(info, CHA + TIMR, 0);	/* 512 cycles */
	issue_command(info, CHA, CMD_START_TIMER);

	spin_unlock_irqrestore(&info->lock,flags);

	end_time=100;
	while(end_time-- && !info->irq_occurred) {
		msleep_interruptible(10);
	}

	info->testing_irq = false;

	spin_lock_irqsave(&info->lock,flags);
	reset_device(info);
	spin_unlock_irqrestore(&info->lock,flags);

	return info->irq_occurred;
}