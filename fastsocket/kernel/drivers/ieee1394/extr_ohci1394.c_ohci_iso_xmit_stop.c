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
struct ti_ohci {int dummy; } ;
struct TYPE_2__ {int context; } ;
struct ohci_iso_xmit {int /*<<< orphan*/  ContextControlClear; struct ti_ohci* ohci; TYPE_1__ task; } ;
struct hpsb_iso {struct ohci_iso_xmit* hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  OHCI1394_IsoXmitIntMaskClear ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ohci1394_stop_context (struct ti_ohci*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_write (struct ti_ohci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ohci_iso_xmit_stop(struct hpsb_iso *iso)
{
	struct ohci_iso_xmit *xmit = iso->hostdata;
	struct ti_ohci *ohci = xmit->ohci;

	/* disable interrupts */
	reg_write(xmit->ohci, OHCI1394_IsoXmitIntMaskClear, 1 << xmit->task.context);

	/* halt DMA */
	if (ohci1394_stop_context(xmit->ohci, xmit->ContextControlClear, NULL)) {
		/* XXX the DMA context will lock up if you try to send too much data! */
		PRINT(KERN_ERR,
		      "you probably exceeded the OHCI card's bandwidth limit - "
		      "reload the module and reduce xmit bandwidth");
	}
}