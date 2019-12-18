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
struct Scsi_Host {scalar_t__ irq; } ;

/* Variables and functions */
 scalar_t__ SCSI_IRQ_NONE ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct Scsi_Host*) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 scalar_t__ sun3_scsi_regp ; 

int sun3scsi_release (struct Scsi_Host *shpnt)
{
	if (shpnt->irq != SCSI_IRQ_NONE)
		free_irq(shpnt->irq, shpnt);

	iounmap((void *)sun3_scsi_regp);

	return 0;
}