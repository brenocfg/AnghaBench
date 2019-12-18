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
struct cx88_core {int dummy; } ;
struct cx8802_dev {struct cx88_core* core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MO_PCI_INTMSK ; 
 int /*<<< orphan*/  MO_TS_DMACNTRL ; 
 int /*<<< orphan*/  MO_TS_INTMSK ; 
 int PCI_INT_TSINT ; 
 int /*<<< orphan*/  TS_GEN_CNTRL ; 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 

__attribute__((used)) static int cx8802_stop_dma(struct cx8802_dev *dev)
{
	struct cx88_core *core = dev->core;
	dprintk( 1, "cx8802_stop_dma\n" );

	/* stop dma */
	cx_clear(MO_TS_DMACNTRL, 0x11);

	/* disable irqs */
	cx_clear(MO_PCI_INTMSK, PCI_INT_TSINT);
	cx_clear(MO_TS_INTMSK, 0x1f0011);

	/* Reset the controller */
	cx_write(TS_GEN_CNTRL, 0xcd);
	return 0;
}