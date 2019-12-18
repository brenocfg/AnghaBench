#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ahc_softc {int /*<<< orphan*/  dev_softc; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  TYPE_1__* bus_dma_tag_t ;
struct TYPE_3__ {int /*<<< orphan*/  maxsize; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* pci_alloc_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
ahc_dmamem_alloc(struct ahc_softc *ahc, bus_dma_tag_t dmat, void** vaddr,
		 int flags, bus_dmamap_t *mapp)
{
	*vaddr = pci_alloc_consistent(ahc->dev_softc,
				      dmat->maxsize, mapp);
	if (*vaddr == NULL)
		return ENOMEM;
	return 0;
}