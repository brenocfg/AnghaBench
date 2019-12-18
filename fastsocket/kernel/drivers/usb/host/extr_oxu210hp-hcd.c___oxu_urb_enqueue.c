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
struct usb_hcd {int dummy; } ;
struct urb {TYPE_1__* dev; int /*<<< orphan*/  pipe; } ;
struct oxu_hcd {int dummy; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
#define  PIPE_BULK 131 
#define  PIPE_CONTROL 130 
#define  PIPE_INTERRUPT 129 
#define  PIPE_ISOCHRONOUS 128 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 struct oxu_hcd* hcd_to_oxu (struct usb_hcd*) ; 
 int intr_submit (struct oxu_hcd*,struct urb*,struct list_head*,int /*<<< orphan*/ ) ; 
 int itd_submit (struct oxu_hcd*,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qh_urb_transaction (struct oxu_hcd*,struct urb*,struct list_head*,int /*<<< orphan*/ ) ; 
 int sitd_submit (struct oxu_hcd*,struct urb*,int /*<<< orphan*/ ) ; 
 int submit_async (struct oxu_hcd*,struct urb*,struct list_head*,int /*<<< orphan*/ ) ; 
 int usb_pipetype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __oxu_urb_enqueue(struct usb_hcd *hcd, struct urb *urb,
				gfp_t mem_flags)
{
	struct oxu_hcd *oxu = hcd_to_oxu(hcd);
	struct list_head qtd_list;

	INIT_LIST_HEAD(&qtd_list);

	switch (usb_pipetype(urb->pipe)) {
	case PIPE_CONTROL:
	case PIPE_BULK:
	default:
		if (!qh_urb_transaction(oxu, urb, &qtd_list, mem_flags))
			return -ENOMEM;
		return submit_async(oxu, urb, &qtd_list, mem_flags);

	case PIPE_INTERRUPT:
		if (!qh_urb_transaction(oxu, urb, &qtd_list, mem_flags))
			return -ENOMEM;
		return intr_submit(oxu, urb, &qtd_list, mem_flags);

	case PIPE_ISOCHRONOUS:
		if (urb->dev->speed == USB_SPEED_HIGH)
			return itd_submit(oxu, urb, mem_flags);
		else
			return sitd_submit(oxu, urb, mem_flags);
	}
}