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
struct Scsi_Host {scalar_t__ irq; int /*<<< orphan*/  n_io_port; int /*<<< orphan*/  io_port; } ;

/* Variables and functions */
 int found ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct Scsi_Host**) ; 
 struct Scsi_Host** hosts ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fd_mcs_release(struct Scsi_Host *shpnt)
{
	int i, this_host, irq_usage;

	release_region(shpnt->io_port, shpnt->n_io_port);

	this_host = -1;
	irq_usage = 0;
	for (i = 0; i < found; i++) {
		if (shpnt == hosts[i])
			this_host = i;
		if (shpnt->irq == hosts[i]->irq)
			irq_usage++;
	}

	/* only for the last one */
	if (1 == irq_usage)
		free_irq(shpnt->irq, hosts);

	found--;

	for (i = this_host; i < found; i++)
		hosts[i] = hosts[i + 1];

	hosts[found] = NULL;

	return 0;
}