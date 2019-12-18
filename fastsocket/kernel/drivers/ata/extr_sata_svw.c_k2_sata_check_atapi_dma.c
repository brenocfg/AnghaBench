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
typedef  int u8 ;
struct ata_queued_cmd {TYPE_2__* ap; TYPE_1__* scsicmd; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int* cmnd; } ;

/* Variables and functions */
 int K2_FLAG_NO_ATAPI_DMA ; 
#define  READ_10 133 
#define  READ_12 132 
#define  READ_16 131 
#define  WRITE_10 130 
#define  WRITE_12 129 
#define  WRITE_16 128 

__attribute__((used)) static int k2_sata_check_atapi_dma(struct ata_queued_cmd *qc)
{
	u8 cmnd = qc->scsicmd->cmnd[0];

	if (qc->ap->flags & K2_FLAG_NO_ATAPI_DMA)
		return -1;	/* ATAPI DMA not supported */
	else {
		switch (cmnd) {
		case READ_10:
		case READ_12:
		case READ_16:
		case WRITE_10:
		case WRITE_12:
		case WRITE_16:
			return 0;

		default:
			return -1;
		}

	}
}