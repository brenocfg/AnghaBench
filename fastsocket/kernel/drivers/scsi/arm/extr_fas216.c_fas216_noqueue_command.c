#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_4__* device; } ;
struct TYPE_9__ {scalar_t__ irq; } ;
struct TYPE_13__ {TYPE_2__* host; scalar_t__ internal_done; TYPE_1__ scsi; } ;
struct TYPE_12__ {TYPE_3__* host; } ;
struct TYPE_11__ {scalar_t__ hostdata; } ;
struct TYPE_10__ {int /*<<< orphan*/  host_lock; } ;
typedef  TYPE_5__ FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ NO_IRQ ; 
 int /*<<< orphan*/  REG_STAT ; 
 int STAT_INT ; 
 int /*<<< orphan*/  fas216_checkmagic (TYPE_5__*) ; 
 int /*<<< orphan*/  fas216_internal_done ; 
 int /*<<< orphan*/  fas216_intr (TYPE_5__*) ; 
 int /*<<< orphan*/  fas216_queue_command (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int fas216_readb (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

int fas216_noqueue_command(struct scsi_cmnd *SCpnt,
			   void (*done)(struct scsi_cmnd *))
{
	FAS216_Info *info = (FAS216_Info *)SCpnt->device->host->hostdata;

	fas216_checkmagic(info);

	/*
	 * We should only be using this if we don't have an interrupt.
	 * Provide some "incentive" to use the queueing code.
	 */
	BUG_ON(info->scsi.irq != NO_IRQ);

	info->internal_done = 0;
	fas216_queue_command(SCpnt, fas216_internal_done);

	/*
	 * This wastes time, since we can't return until the command is
	 * complete. We can't sleep either since we may get re-entered!
	 * However, we must re-enable interrupts, or else we'll be
	 * waiting forever.
	 */
	spin_unlock_irq(info->host->host_lock);

	while (!info->internal_done) {
		/*
		 * If we don't have an IRQ, then we must poll the card for
		 * it's interrupt, and use that to call this driver's
		 * interrupt routine.  That way, we keep the command
		 * progressing.  Maybe we can add some inteligence here
		 * and go to sleep if we know that the device is going
		 * to be some time (eg, disconnected).
		 */
		if (fas216_readb(info, REG_STAT) & STAT_INT) {
			spin_lock_irq(info->host->host_lock);
			fas216_intr(info);
			spin_unlock_irq(info->host->host_lock);
		}
	}

	spin_lock_irq(info->host->host_lock);

	done(SCpnt);

	return 0;
}