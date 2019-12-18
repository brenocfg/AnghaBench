#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_6__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_5__ {scalar_t__ dma_base; } ;

/* Variables and functions */
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  trm290_prepare_drive (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trm290_dma_end(ide_drive_t *drive)
{
	u16 status = inw(drive->hwif->dma_base + 2);

	trm290_prepare_drive(drive, 0);

	return status != 0x00ff;
}