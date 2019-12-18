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
 int /*<<< orphan*/  APR ; 
 int /*<<< orphan*/  CCFR ; 
 int /*<<< orphan*/  CCTR ; 
 int /*<<< orphan*/  ___set_DMAC (unsigned long,int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_1__* frv_dma_channels ; 
 int /*<<< orphan*/  mb () ; 

void frv_dma_config(int dma, unsigned long ccfr, unsigned long cctr, unsigned long apr)
{
	unsigned long ioaddr = frv_dma_channels[dma].ioaddr;

	___set_DMAC(ioaddr, CCFR, ccfr);
	___set_DMAC(ioaddr, CCTR, cctr);
	___set_DMAC(ioaddr, APR,  apr);
	mb();

}