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
struct scsi_target {int dummy; } ;
struct TYPE_3__ {scalar_t__ ioport; int /*<<< orphan*/ * maddr; } ;
struct ahc_softc {scalar_t__ tag; TYPE_2__* platform_data; TYPE_1__ bsh; } ;
struct TYPE_4__ {scalar_t__ irq; scalar_t__ host; int /*<<< orphan*/  mem_busaddr; struct scsi_target** starget; } ;

/* Variables and functions */
 scalar_t__ AHC_LINUX_NOIRQ ; 
 int AHC_NUM_TARGETS ; 
 scalar_t__ BUS_SPACE_MEMIO ; 
 scalar_t__ BUS_SPACE_PIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct ahc_softc*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 
 int /*<<< orphan*/  scsi_host_put (scalar_t__) ; 

void
ahc_platform_free(struct ahc_softc *ahc)
{
	struct scsi_target *starget;
	int i;

	if (ahc->platform_data != NULL) {
		/* destroy all of the device and target objects */
		for (i = 0; i < AHC_NUM_TARGETS; i++) {
			starget = ahc->platform_data->starget[i];
			if (starget != NULL) {
				ahc->platform_data->starget[i] = NULL;
 			}
 		}

		if (ahc->platform_data->irq != AHC_LINUX_NOIRQ)
			free_irq(ahc->platform_data->irq, ahc);
		if (ahc->tag == BUS_SPACE_PIO
		 && ahc->bsh.ioport != 0)
			release_region(ahc->bsh.ioport, 256);
		if (ahc->tag == BUS_SPACE_MEMIO
		 && ahc->bsh.maddr != NULL) {
			iounmap(ahc->bsh.maddr);
			release_mem_region(ahc->platform_data->mem_busaddr,
					   0x1000);
		}

		if (ahc->platform_data->host)
			scsi_host_put(ahc->platform_data->host);

		free(ahc->platform_data, M_DEVBUF);
	}
}