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
struct ata_queued_cmd {unsigned int n_elem; unsigned int orig_n_elem; int /*<<< orphan*/  flags; int /*<<< orphan*/  dma_dir; int /*<<< orphan*/  sg; struct ata_port* ap; } ;
struct ata_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  print_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_QCFLAG_DMAMAP ; 
 int /*<<< orphan*/  DPRINTK (char*,unsigned int) ; 
 int /*<<< orphan*/  VPRINTK (char*,int /*<<< orphan*/ ) ; 
 unsigned int dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ata_sg_setup(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	unsigned int n_elem;

	VPRINTK("ENTER, ata%u\n", ap->print_id);

	n_elem = dma_map_sg(ap->dev, qc->sg, qc->n_elem, qc->dma_dir);
	if (n_elem < 1)
		return -1;

	DPRINTK("%d sg elements mapped\n", n_elem);
	qc->orig_n_elem = qc->n_elem;
	qc->n_elem = n_elem;
	qc->flags |= ATA_QCFLAG_DMAMAP;

	return 0;
}