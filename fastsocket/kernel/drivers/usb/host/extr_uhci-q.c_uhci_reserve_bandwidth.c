#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct uhci_qh {int load; int phase; int period; int type; int bandwidth_reserved; TYPE_4__* hep; TYPE_2__* udev; } ;
struct uhci_hcd {int* load; int total_load; } ;
struct TYPE_6__ {int bandwidth_allocated; int /*<<< orphan*/  bandwidth_isoc_reqs; int /*<<< orphan*/  bandwidth_int_reqs; } ;
struct TYPE_10__ {TYPE_1__ self; } ;
struct TYPE_8__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_9__ {TYPE_3__ desc; } ;
struct TYPE_7__ {int /*<<< orphan*/  devnum; } ;

/* Variables and functions */
 int MAX_PHASE ; 
#define  USB_ENDPOINT_XFER_INT 129 
#define  USB_ENDPOINT_XFER_ISOC 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  uhci_dev (struct uhci_hcd*) ; 
 TYPE_5__* uhci_to_hcd (struct uhci_hcd*) ; 

__attribute__((used)) static void uhci_reserve_bandwidth(struct uhci_hcd *uhci, struct uhci_qh *qh)
{
	int i;
	int load = qh->load;
	char *p = "??";

	for (i = qh->phase; i < MAX_PHASE; i += qh->period) {
		uhci->load[i] += load;
		uhci->total_load += load;
	}
	uhci_to_hcd(uhci)->self.bandwidth_allocated =
			uhci->total_load / MAX_PHASE;
	switch (qh->type) {
	case USB_ENDPOINT_XFER_INT:
		++uhci_to_hcd(uhci)->self.bandwidth_int_reqs;
		p = "INT";
		break;
	case USB_ENDPOINT_XFER_ISOC:
		++uhci_to_hcd(uhci)->self.bandwidth_isoc_reqs;
		p = "ISO";
		break;
	}
	qh->bandwidth_reserved = 1;
	dev_dbg(uhci_dev(uhci),
			"%s dev %d ep%02x-%s, period %d, phase %d, %d us\n",
			"reserve", qh->udev->devnum,
			qh->hep->desc.bEndpointAddress, p,
			qh->period, qh->phase, load);
}