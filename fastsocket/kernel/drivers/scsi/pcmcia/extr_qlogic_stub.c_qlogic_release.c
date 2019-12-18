#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  AssignedIRQ; } ;
struct pcmcia_device {TYPE_1__ irq; TYPE_2__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;
typedef  TYPE_2__ scsi_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,struct pcmcia_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qlogic_release(struct pcmcia_device *link)
{
	scsi_info_t *info = link->priv;

	DEBUG(0, "qlogic_release(0x%p)\n", link);

	scsi_remove_host(info->host);

	free_irq(link->irq.AssignedIRQ, info->host);
	pcmcia_disable_device(link);

	scsi_host_put(info->host);
}