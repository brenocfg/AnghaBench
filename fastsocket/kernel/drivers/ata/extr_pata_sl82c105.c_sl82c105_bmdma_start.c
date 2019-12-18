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
struct ata_queued_cmd {int /*<<< orphan*/  dev; struct ata_port* ap; } ;
struct ata_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_bmdma_start (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  sl82c105_configure_dmamode (struct ata_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sl82c105_reset_engine (struct ata_port*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sl82c105_bmdma_start(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;

	udelay(100);
	sl82c105_reset_engine(ap);
	udelay(100);

	/* Set the clocks for DMA */
	sl82c105_configure_dmamode(ap, qc->dev);
	/* Activate DMA */
	ata_bmdma_start(qc);
}