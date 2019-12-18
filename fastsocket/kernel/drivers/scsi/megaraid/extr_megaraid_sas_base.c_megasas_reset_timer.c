#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_2__* device; scalar_t__ jiffies_at_alloc; } ;
struct megasas_instance {int flag; TYPE_3__* host; int /*<<< orphan*/  last_time; int /*<<< orphan*/  throttlequeuedepth; } ;
typedef  enum blk_eh_timer_return { ____Placeholder_blk_eh_timer_return } blk_eh_timer_return ;
struct TYPE_6__ {int /*<<< orphan*/  host_lock; int /*<<< orphan*/  can_queue; } ;
struct TYPE_5__ {TYPE_1__* host; } ;
struct TYPE_4__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int BLK_EH_NOT_HANDLED ; 
 int BLK_EH_RESET_TIMER ; 
 int HZ ; 
 int MEGASAS_DEFAULT_CMD_TIMEOUT ; 
 int MEGASAS_FW_BUSY ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static enum
blk_eh_timer_return megasas_reset_timer(struct scsi_cmnd *scmd)
{
	struct megasas_instance *instance;
	unsigned long flags;

	if (time_after(jiffies, scmd->jiffies_at_alloc +
				(MEGASAS_DEFAULT_CMD_TIMEOUT * 2) * HZ)) {
		return BLK_EH_NOT_HANDLED;
	}

	instance = (struct megasas_instance *)scmd->device->host->hostdata;
	if (!(instance->flag & MEGASAS_FW_BUSY)) {
		/* FW is busy, throttle IO */
		spin_lock_irqsave(instance->host->host_lock, flags);

		instance->host->can_queue = instance->throttlequeuedepth;
		instance->last_time = jiffies;
		instance->flag |= MEGASAS_FW_BUSY;

		spin_unlock_irqrestore(instance->host->host_lock, flags);
	}
	return BLK_EH_RESET_TIMER;
}