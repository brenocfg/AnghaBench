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
typedef  scalar_t__ usb_complete_t ;
struct usb_device {int dummy; } ;
struct urb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,struct usb_device*,unsigned int,void*,int,scalar_t__,void*) ; 

void RTUSB_FILL_BULK_URB (struct urb *pUrb,
	struct usb_device *pUsb_Dev,
	unsigned int bulkpipe,
	void *pTransferBuf,
	int BufSize,
	usb_complete_t Complete,
	void *pContext)
{

	usb_fill_bulk_urb(pUrb, pUsb_Dev, bulkpipe, pTransferBuf, BufSize, (usb_complete_t)Complete, pContext);

}