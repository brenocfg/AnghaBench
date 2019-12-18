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
struct TYPE_2__ {unsigned long ioaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCL ; 
 int /*<<< orphan*/  CSTR ; 
 int /*<<< orphan*/  PIX ; 
 int /*<<< orphan*/  SIX ; 
 unsigned long __get_DMAC (unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_1__* frv_dma_channels ; 
 int /*<<< orphan*/  printk (char*,int,unsigned long,unsigned long,unsigned long,unsigned long) ; 

void frv_dma_dump(int dma)
{
	unsigned long ioaddr = frv_dma_channels[dma].ioaddr;
	unsigned long cstr, pix, six, bcl;

	cstr = __get_DMAC(ioaddr, CSTR);
	pix  = __get_DMAC(ioaddr, PIX);
	six  = __get_DMAC(ioaddr, SIX);
	bcl  = __get_DMAC(ioaddr, BCL);

	printk("DMA[%d] cstr=%lx pix=%lx six=%lx bcl=%lx\n", dma, cstr, pix, six, bcl);

}