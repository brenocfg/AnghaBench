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
struct packet {int /*<<< orphan*/ * priv_data; scalar_t__ info; int /*<<< orphan*/  status; scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct fhci_usb {TYPE_1__* ep0; } ;
struct TYPE_2__ {int /*<<< orphan*/  empty_frame_Q; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_TD_OK ; 
 int /*<<< orphan*/  cq_put (int /*<<< orphan*/ ,struct packet*) ; 

__attribute__((used)) static void recycle_frame(struct fhci_usb *usb, struct packet *pkt)
{
	pkt->data = NULL;
	pkt->len = 0;
	pkt->status = USB_TD_OK;
	pkt->info = 0;
	pkt->priv_data = NULL;

	cq_put(usb->ep0->empty_frame_Q, pkt);
}