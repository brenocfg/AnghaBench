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
struct smsusb_device_t {int /*<<< orphan*/  udev; } ;
struct SmsMsgHdr_ST {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  smsendian_handle_message_header (struct SmsMsgHdr_ST*) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smsusb_sendrequest(void *context, void *buffer, size_t size)
{
	struct smsusb_device_t *dev = (struct smsusb_device_t *) context;
	int dummy;

	smsendian_handle_message_header((struct SmsMsgHdr_ST *)buffer);
	return usb_bulk_msg(dev->udev, usb_sndbulkpipe(dev->udev, 2),
			    buffer, size, &dummy, 1000);
}