#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ata_port {int pflags; int /*<<< orphan*/  scsi_host; int /*<<< orphan*/  hotplug_task; int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  error_handler; } ;

/* Variables and functions */
 int ATA_PFLAG_UNLOADED ; 
 int ATA_PFLAG_UNLOADING ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ata_port_schedule_eh (struct ata_port*) ; 
 int /*<<< orphan*/  ata_port_wait_eh (struct ata_port*) ; 
 int /*<<< orphan*/  cancel_rearming_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void ata_port_detach(struct ata_port *ap)
{
	unsigned long flags;

	if (!ap->ops->error_handler)
		goto skip_eh;

	/* tell EH we're leaving & flush EH */
	spin_lock_irqsave(ap->lock, flags);
	ap->pflags |= ATA_PFLAG_UNLOADING;
	ata_port_schedule_eh(ap);
	spin_unlock_irqrestore(ap->lock, flags);

	/* wait till EH commits suicide */
	ata_port_wait_eh(ap);

	/* it better be dead now */
	WARN_ON(!(ap->pflags & ATA_PFLAG_UNLOADED));

	cancel_rearming_delayed_work(&ap->hotplug_task);

 skip_eh:
	/* remove the associated SCSI host */
	scsi_remove_host(ap->scsi_host);
}