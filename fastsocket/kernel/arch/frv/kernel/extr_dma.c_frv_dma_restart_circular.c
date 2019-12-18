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
 int /*<<< orphan*/  CCTR ; 
 int /*<<< orphan*/  CSTR ; 
 unsigned long DMAC_CCTRx_ACT ; 
 unsigned long DMAC_CSTRx_CE ; 
 int /*<<< orphan*/  SIX ; 
 int /*<<< orphan*/  ___set_DMAC (unsigned long,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long __get_DMAC (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_DMAC (unsigned long,int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_1__* frv_dma_channels ; 
 int /*<<< orphan*/  frv_set_dma_inprogress (int) ; 
 int /*<<< orphan*/  mb () ; 

void frv_dma_restart_circular(int dma, unsigned long six)
{
	unsigned long ioaddr = frv_dma_channels[dma].ioaddr;

	___set_DMAC(ioaddr, SIX,  six);
	___set_DMAC(ioaddr, CSTR, __get_DMAC(ioaddr, CSTR) & ~DMAC_CSTRx_CE);
	mb();

	__set_DMAC(ioaddr, CCTR, __get_DMAC(ioaddr, CCTR) | DMAC_CCTRx_ACT);
	frv_set_dma_inprogress(dma);

}