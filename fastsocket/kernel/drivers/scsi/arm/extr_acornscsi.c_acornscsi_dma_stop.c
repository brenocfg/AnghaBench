#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  SCpnt; } ;
typedef  TYPE_1__ AS_Host ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMAC_MASKREG ; 
 int /*<<< orphan*/  MASK_ON ; 
 int /*<<< orphan*/  acornscsi_dumpdma (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dmac_clearintr (TYPE_1__*) ; 
 int /*<<< orphan*/  dmac_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void acornscsi_dma_stop(AS_Host *host)
{
    dmac_write(host, DMAC_MASKREG, MASK_ON);
    dmac_clearintr(host);

#if (DEBUG & DEBUG_DMA)
    DBG(host->SCpnt, acornscsi_dumpdma(host, "stop"));
#endif
}