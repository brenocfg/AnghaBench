#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ide_port_ops {int /*<<< orphan*/  (* set_pio_mode ) (TYPE_2__*,int) ;} ;
struct TYPE_9__ {int host_flags; int /*<<< orphan*/  lock; struct ide_port_ops* port_ops; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_10__ {int dev_flags; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int IDE_DFLAG_USING_DMA ; 
 int IDE_HFLAG_NO_SET_MODE ; 
 int IDE_HFLAG_SET_PIO_MODE_KEEP_DMA ; 
 int /*<<< orphan*/  ide_dma_on (TYPE_2__*) ; 
 int /*<<< orphan*/  ide_set_pio (TYPE_2__*,int) ; 
 scalar_t__ set_pio_mode_abuse (TYPE_1__*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int) ; 

__attribute__((used)) static int set_pio_mode(ide_drive_t *drive, int arg)
{
	ide_hwif_t *hwif = drive->hwif;
	const struct ide_port_ops *port_ops = hwif->port_ops;

	if (arg < 0 || arg > 255)
		return -EINVAL;

	if (port_ops == NULL || port_ops->set_pio_mode == NULL ||
	    (hwif->host_flags & IDE_HFLAG_NO_SET_MODE))
		return -ENOSYS;

	if (set_pio_mode_abuse(drive->hwif, arg)) {
		if (arg == 8 || arg == 9) {
			unsigned long flags;

			/* take lock for IDE_DFLAG_[NO_]UNMASK/[NO_]IO_32BIT */
			spin_lock_irqsave(&hwif->lock, flags);
			port_ops->set_pio_mode(drive, arg);
			spin_unlock_irqrestore(&hwif->lock, flags);
		} else
			port_ops->set_pio_mode(drive, arg);
	} else {
		int keep_dma = !!(drive->dev_flags & IDE_DFLAG_USING_DMA);

		ide_set_pio(drive, arg);

		if (hwif->host_flags & IDE_HFLAG_SET_PIO_MODE_KEEP_DMA) {
			if (keep_dma)
				ide_dma_on(drive);
		}
	}

	return 0;
}