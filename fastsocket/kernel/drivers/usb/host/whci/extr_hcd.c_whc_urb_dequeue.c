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
struct wusbhc {int dummy; } ;
struct whc {int dummy; } ;
struct usb_hcd {int dummy; } ;
struct urb {int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  PIPE_BULK 131 
#define  PIPE_CONTROL 130 
#define  PIPE_INTERRUPT 129 
#define  PIPE_ISOCHRONOUS 128 
 int asl_urb_dequeue (struct whc*,struct urb*,int) ; 
 int pzl_urb_dequeue (struct whc*,struct urb*,int) ; 
 struct wusbhc* usb_hcd_to_wusbhc (struct usb_hcd*) ; 
 int usb_pipetype (int /*<<< orphan*/ ) ; 
 struct whc* wusbhc_to_whc (struct wusbhc*) ; 

__attribute__((used)) static int whc_urb_dequeue(struct usb_hcd *usb_hcd, struct urb *urb, int status)
{
	struct wusbhc *wusbhc = usb_hcd_to_wusbhc(usb_hcd);
	struct whc *whc = wusbhc_to_whc(wusbhc);
	int ret;

	switch (usb_pipetype(urb->pipe)) {
	case PIPE_INTERRUPT:
		ret = pzl_urb_dequeue(whc, urb, status);
		break;
	case PIPE_ISOCHRONOUS:
		ret = -ENOTSUPP;
		break;
	case PIPE_CONTROL:
	case PIPE_BULK:
	default:
		ret = asl_urb_dequeue(whc, urb, status);
		break;
	};

	return ret;
}