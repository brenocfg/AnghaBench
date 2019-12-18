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
typedef  int uint32_t ;
struct TYPE_2__ {unsigned long ioaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCL ; 
 int /*<<< orphan*/  CCTR ; 
 int /*<<< orphan*/  CSTR ; 
 int DMAC_CCTRx_ACT ; 
 int DMAC_CCTRx_FC ; 
 int DMAC_CCTRx_IE ; 
 int /*<<< orphan*/  ___set_DMAC (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __get_DMAC (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_DMAC (unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  frv_clear_dma_inprogress (int) ; 
 TYPE_1__* frv_dma_channels ; 

void frv_dma_stop(int dma)
{
	unsigned long ioaddr = frv_dma_channels[dma].ioaddr;
	uint32_t cctr;

	___set_DMAC(ioaddr, CSTR, 0);
	cctr = __get_DMAC(ioaddr, CCTR);
	cctr &= ~(DMAC_CCTRx_IE | DMAC_CCTRx_ACT);
	cctr |= DMAC_CCTRx_FC; 	/* fifo clear */
	__set_DMAC(ioaddr, CCTR, cctr);
	__set_DMAC(ioaddr, BCL,  0);
	frv_clear_dma_inprogress(dma);
}