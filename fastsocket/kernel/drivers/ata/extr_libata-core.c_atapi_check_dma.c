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
struct ata_queued_cmd {int nbytes; TYPE_1__* dev; struct ata_port* ap; } ;
struct ata_port {TYPE_2__* ops; } ;
struct TYPE_4__ {int (* check_atapi_dma ) (struct ata_queued_cmd*) ;} ;
struct TYPE_3__ {int horkage; } ;

/* Variables and functions */
 int ATA_HORKAGE_ATAPI_MOD16_DMA ; 
 int stub1 (struct ata_queued_cmd*) ; 
 scalar_t__ unlikely (int) ; 

int atapi_check_dma(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;

	/* Don't allow DMA if it isn't multiple of 16 bytes.  Quite a
	 * few ATAPI devices choke on such DMA requests.
	 */
	if (!(qc->dev->horkage & ATA_HORKAGE_ATAPI_MOD16_DMA) &&
	    unlikely(qc->nbytes & 15))
		return 1;

	if (ap->ops->check_atapi_dma)
		return ap->ops->check_atapi_dma(qc);

	return 0;
}