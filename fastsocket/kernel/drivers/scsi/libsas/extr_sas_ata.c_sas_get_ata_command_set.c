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
struct TYPE_2__ {void* command_set; } ;
struct domain_device {scalar_t__ dev_type; TYPE_1__ sata_dev; scalar_t__ frame_rcvd; } ;
struct dev_to_host_fis {int sector_count; int lbal; int lbam; int lbah; int device; int interrupt_reason; int byte_count_low; int byte_count_high; } ;

/* Variables and functions */
 void* ATAPI_COMMAND_SET ; 
 void* ATA_COMMAND_SET ; 
 scalar_t__ SATA_PENDING ; 

__attribute__((used)) static void sas_get_ata_command_set(struct domain_device *dev)
{
	struct dev_to_host_fis *fis =
		(struct dev_to_host_fis *) dev->frame_rcvd;

	if (dev->dev_type == SATA_PENDING)
		return;

	if ((fis->sector_count == 1 && /* ATA */
	     fis->lbal         == 1 &&
	     fis->lbam         == 0 &&
	     fis->lbah         == 0 &&
	     fis->device       == 0)
	    ||
	    (fis->sector_count == 0 && /* CE-ATA (mATA) */
	     fis->lbal         == 0 &&
	     fis->lbam         == 0xCE &&
	     fis->lbah         == 0xAA &&
	     (fis->device & ~0x10) == 0))

		dev->sata_dev.command_set = ATA_COMMAND_SET;

	else if ((fis->interrupt_reason == 1 &&	/* ATAPI */
		  fis->lbal             == 1 &&
		  fis->byte_count_low   == 0x14 &&
		  fis->byte_count_high  == 0xEB &&
		  (fis->device & ~0x10) == 0))

		dev->sata_dev.command_set = ATAPI_COMMAND_SET;

	else if ((fis->sector_count == 1 && /* SEMB */
		  fis->lbal         == 1 &&
		  fis->lbam         == 0x3C &&
		  fis->lbah         == 0xC3 &&
		  fis->device       == 0)
		||
		 (fis->interrupt_reason == 1 &&	/* SATA PM */
		  fis->lbal             == 1 &&
		  fis->byte_count_low   == 0x69 &&
		  fis->byte_count_high  == 0x96 &&
		  (fis->device & ~0x10) == 0))

		/* Treat it as a superset? */
		dev->sata_dev.command_set = ATAPI_COMMAND_SET;
}