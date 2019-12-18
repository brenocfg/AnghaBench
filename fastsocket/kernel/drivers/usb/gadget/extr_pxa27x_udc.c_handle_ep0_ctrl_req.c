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
typedef  void* u32 ;
struct usb_ctrlrequest {int bRequestType; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; } ;
struct pxa_udc {int /*<<< orphan*/  gadget; TYPE_1__* driver; struct pxa_ep* pxa_ep; } ;
struct pxa_ep {int dummy; } ;
struct pxa27x_request {int dummy; } ;
struct TYPE_2__ {int (* setup ) (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EPROTO ; 
 int /*<<< orphan*/  IN_DATA_STAGE ; 
 int /*<<< orphan*/  OUT_DATA_STAGE ; 
 int /*<<< orphan*/  STALL ; 
 int /*<<< orphan*/  UDCCSR ; 
 int UDCCSR0_FST ; 
 int UDCCSR0_FTF ; 
 int UDCCSR0_OPC ; 
 int UDCCSR0_SA ; 
 int /*<<< orphan*/  UDCDR ; 
 int USB_DIR_IN ; 
 scalar_t__ ep_count_bytes_remain (struct pxa_ep*) ; 
 int /*<<< orphan*/  ep_dbg (struct pxa_ep*,char*,void*,int,...) ; 
 int /*<<< orphan*/  ep_err (struct pxa_ep*,char*,int) ; 
 int ep_is_empty (struct pxa_ep*) ; 
 int /*<<< orphan*/  ep_write_UDCCSR (struct pxa_ep*,int) ; 
 scalar_t__ epout_has_pkt (struct pxa_ep*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nuke (struct pxa_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ep0state (struct pxa_udc*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ; 
 void* udc_ep_readl (struct pxa_ep*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void handle_ep0_ctrl_req(struct pxa_udc *udc,
				struct pxa27x_request *req)
{
	struct pxa_ep *ep = &udc->pxa_ep[0];
	union {
		struct usb_ctrlrequest	r;
		u32			word[2];
	} u;
	int i;
	int have_extrabytes = 0;

	nuke(ep, -EPROTO);

	/*
	 * In the PXA320 manual, in the section about Back-to-Back setup
	 * packets, it describes this situation.  The solution is to set OPC to
	 * get rid of the status packet, and then continue with the setup
	 * packet. Generalize to pxa27x CPUs.
	 */
	if (epout_has_pkt(ep) && (ep_count_bytes_remain(ep) == 0))
		ep_write_UDCCSR(ep, UDCCSR0_OPC);

	/* read SETUP packet */
	for (i = 0; i < 2; i++) {
		if (unlikely(ep_is_empty(ep)))
			goto stall;
		u.word[i] = udc_ep_readl(ep, UDCDR);
	}

	have_extrabytes = !ep_is_empty(ep);
	while (!ep_is_empty(ep)) {
		i = udc_ep_readl(ep, UDCDR);
		ep_err(ep, "wrong to have extra bytes for setup : 0x%08x\n", i);
	}

	ep_dbg(ep, "SETUP %02x.%02x v%04x i%04x l%04x\n",
		u.r.bRequestType, u.r.bRequest,
		le16_to_cpu(u.r.wValue), le16_to_cpu(u.r.wIndex),
		le16_to_cpu(u.r.wLength));
	if (unlikely(have_extrabytes))
		goto stall;

	if (u.r.bRequestType & USB_DIR_IN)
		set_ep0state(udc, IN_DATA_STAGE);
	else
		set_ep0state(udc, OUT_DATA_STAGE);

	/* Tell UDC to enter Data Stage */
	ep_write_UDCCSR(ep, UDCCSR0_SA | UDCCSR0_OPC);

	i = udc->driver->setup(&udc->gadget, &u.r);
	if (i < 0)
		goto stall;
out:
	return;
stall:
	ep_dbg(ep, "protocol STALL, udccsr0=%03x err %d\n",
		udc_ep_readl(ep, UDCCSR), i);
	ep_write_UDCCSR(ep, UDCCSR0_FST | UDCCSR0_FTF);
	set_ep0state(udc, STALL);
	goto out;
}