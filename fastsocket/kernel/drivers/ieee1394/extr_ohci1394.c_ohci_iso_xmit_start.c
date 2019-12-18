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
typedef  int u32 ;
struct ti_ohci {int dummy; } ;
struct TYPE_2__ {int context; } ;
struct ohci_iso_xmit {int /*<<< orphan*/  ContextControlSet; struct ti_ohci* ohci; TYPE_1__ task; int /*<<< orphan*/  prog; int /*<<< orphan*/  CommandPtr; int /*<<< orphan*/  ContextControlClear; } ;
struct iso_xmit_cmd {int dummy; } ;
struct hpsb_iso {int pkt_dma; struct ohci_iso_xmit* hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  OHCI1394_IsoXmitIntMaskSet ; 
 int /*<<< orphan*/  OHCI1394_IsochronousCycleTimer ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,char*,int) ; 
 int dma_prog_region_offset_to_bus (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mb () ; 
 int reg_read (struct ti_ohci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct ti_ohci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int ohci_iso_xmit_start(struct hpsb_iso *iso, int cycle)
{
	struct ohci_iso_xmit *xmit = iso->hostdata;
	struct ti_ohci *ohci = xmit->ohci;

	/* clear out the control register */
	reg_write(xmit->ohci, xmit->ContextControlClear, 0xFFFFFFFF);
	wmb();

	/* address and length of first descriptor block (Z=3) */
	reg_write(xmit->ohci, xmit->CommandPtr,
		  dma_prog_region_offset_to_bus(&xmit->prog, iso->pkt_dma * sizeof(struct iso_xmit_cmd)) | 3);

	/* cycle match */
	if (cycle != -1) {
		u32 start = cycle & 0x1FFF;

		/* 'cycle' is only mod 8000, but we also need two 'seconds' bits -
		   just snarf them from the current time */
		u32 seconds = reg_read(xmit->ohci, OHCI1394_IsochronousCycleTimer) >> 25;

		/* advance one second to give some extra time for DMA to start */
		seconds += 1;

		start |= (seconds & 3) << 13;

		reg_write(xmit->ohci, xmit->ContextControlSet, 0x80000000 | (start << 16));
	}

	/* enable interrupts */
	reg_write(xmit->ohci, OHCI1394_IsoXmitIntMaskSet, 1 << xmit->task.context);

	/* run */
	reg_write(xmit->ohci, xmit->ContextControlSet, 0x8000);
	mb();

	/* wait 100 usec to give the card time to go active */
	udelay(100);

	/* check the RUN bit */
	if (!(reg_read(xmit->ohci, xmit->ContextControlSet) & 0x8000)) {
		PRINT(KERN_ERR, "Error starting IT DMA (ContextControl 0x%08x)\n",
		      reg_read(xmit->ohci, xmit->ContextControlSet));
		return -1;
	}

	return 0;
}