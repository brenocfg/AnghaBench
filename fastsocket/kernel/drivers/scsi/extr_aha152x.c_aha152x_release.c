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
struct Scsi_Host {scalar_t__ io_port; scalar_t__ irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_list; scalar_t__ pnpdev; } ;

/* Variables and functions */
 TYPE_1__* HOSTDATA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  IO_RANGE ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct Scsi_Host*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnp_device_detach (scalar_t__) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

void aha152x_release(struct Scsi_Host *shpnt)
{
	if (!shpnt)
		return;

	scsi_remove_host(shpnt);
	if (shpnt->irq)
		free_irq(shpnt->irq, shpnt);

#if !defined(PCMCIA)
	if (shpnt->io_port)
		release_region(shpnt->io_port, IO_RANGE);
#endif

#ifdef __ISAPNP__
	if (HOSTDATA(shpnt)->pnpdev)
		pnp_device_detach(HOSTDATA(shpnt)->pnpdev);
#endif

	list_del(&HOSTDATA(shpnt)->host_list);
	scsi_host_put(shpnt);
}