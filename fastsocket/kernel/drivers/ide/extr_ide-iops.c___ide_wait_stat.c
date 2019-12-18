#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ide_tp_ops {int (* read_status ) (TYPE_1__*) ;} ;
struct TYPE_8__ {struct ide_tp_ops* tp_ops; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_9__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int ATA_BUSY ; 
 int EBUSY ; 
 int EFAULT ; 
 scalar_t__ OK_STAT (int,int,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  local_irq_enable_in_hardirq () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_save_flags (unsigned long) ; 
 int stub1 (TYPE_1__*) ; 
 int stub2 (TYPE_1__*) ; 
 int stub3 (TYPE_1__*) ; 
 int stub4 (TYPE_1__*) ; 
 scalar_t__ time_after (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

int __ide_wait_stat(ide_drive_t *drive, u8 good, u8 bad,
		    unsigned long timeout, u8 *rstat)
{
	ide_hwif_t *hwif = drive->hwif;
	const struct ide_tp_ops *tp_ops = hwif->tp_ops;
	unsigned long flags;
	int i;
	u8 stat;

	udelay(1);	/* spec allows drive 400ns to assert "BUSY" */
	stat = tp_ops->read_status(hwif);

	if (stat & ATA_BUSY) {
		local_save_flags(flags);
		local_irq_enable_in_hardirq();
		timeout += jiffies;
		while ((stat = tp_ops->read_status(hwif)) & ATA_BUSY) {
			if (time_after(jiffies, timeout)) {
				/*
				 * One last read after the timeout in case
				 * heavy interrupt load made us not make any
				 * progress during the timeout..
				 */
				stat = tp_ops->read_status(hwif);
				if ((stat & ATA_BUSY) == 0)
					break;

				local_irq_restore(flags);
				*rstat = stat;
				return -EBUSY;
			}
		}
		local_irq_restore(flags);
	}
	/*
	 * Allow status to settle, then read it again.
	 * A few rare drives vastly violate the 400ns spec here,
	 * so we'll wait up to 10usec for a "good" status
	 * rather than expensively fail things immediately.
	 * This fix courtesy of Matthew Faupel & Niccolo Rigacci.
	 */
	for (i = 0; i < 10; i++) {
		udelay(1);
		stat = tp_ops->read_status(hwif);

		if (OK_STAT(stat, good, bad)) {
			*rstat = stat;
			return 0;
		}
	}
	*rstat = stat;
	return -EFAULT;
}