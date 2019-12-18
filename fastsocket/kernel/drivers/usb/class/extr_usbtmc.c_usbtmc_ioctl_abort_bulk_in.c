#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct usbtmc_device_data {scalar_t__ bulk_in; int /*<<< orphan*/  usb_dev; TYPE_4__* intf; int /*<<< orphan*/  bTag_last_read; } ;
struct TYPE_5__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_3__* endpoint; TYPE_1__ desc; } ;
struct device {int dummy; } ;
struct TYPE_8__ {struct device dev; struct usb_host_interface* cur_altsetting; } ;
struct TYPE_6__ {scalar_t__ bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_7__ {TYPE_2__ desc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int USBTMC_MAX_READS_TO_CLEAR_BULK_IN ; 
 int /*<<< orphan*/  USBTMC_REQUEST_CHECK_ABORT_BULK_IN_STATUS ; 
 int /*<<< orphan*/  USBTMC_REQUEST_INITIATE_ABORT_BULK_IN ; 
 int /*<<< orphan*/  USBTMC_SIZE_IOBUFFER ; 
 int USBTMC_STATUS_FAILED ; 
 int USBTMC_STATUS_PENDING ; 
 int USBTMC_STATUS_SUCCESS ; 
 int /*<<< orphan*/  USBTMC_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_RECIP_ENDPOINT ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbtmc_ioctl_abort_bulk_in(struct usbtmc_device_data *data)
{
	u8 *buffer;
	struct device *dev;
	int rv;
	int n;
	int actual;
	struct usb_host_interface *current_setting;
	int max_size;

	dev = &data->intf->dev;
	buffer = kmalloc(USBTMC_SIZE_IOBUFFER, GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	rv = usb_control_msg(data->usb_dev,
			     usb_rcvctrlpipe(data->usb_dev, 0),
			     USBTMC_REQUEST_INITIATE_ABORT_BULK_IN,
			     USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_ENDPOINT,
			     data->bTag_last_read, data->bulk_in,
			     buffer, 2, USBTMC_TIMEOUT);

	if (rv < 0) {
		dev_err(dev, "usb_control_msg returned %d\n", rv);
		goto exit;
	}

	dev_dbg(dev, "INITIATE_ABORT_BULK_IN returned %x\n", buffer[0]);

	if (buffer[0] == USBTMC_STATUS_FAILED) {
		rv = 0;
		goto exit;
	}

	if (buffer[0] != USBTMC_STATUS_SUCCESS) {
		dev_err(dev, "INITIATE_ABORT_BULK_IN returned %x\n",
			buffer[0]);
		rv = -EPERM;
		goto exit;
	}

	max_size = 0;
	current_setting = data->intf->cur_altsetting;
	for (n = 0; n < current_setting->desc.bNumEndpoints; n++)
		if (current_setting->endpoint[n].desc.bEndpointAddress ==
			data->bulk_in)
			max_size = le16_to_cpu(current_setting->endpoint[n].
						desc.wMaxPacketSize);

	if (max_size == 0) {
		dev_err(dev, "Couldn't get wMaxPacketSize\n");
		rv = -EPERM;
		goto exit;
	}

	dev_dbg(&data->intf->dev, "wMaxPacketSize is %d\n", max_size);

	n = 0;

	do {
		dev_dbg(dev, "Reading from bulk in EP\n");

		rv = usb_bulk_msg(data->usb_dev,
				  usb_rcvbulkpipe(data->usb_dev,
						  data->bulk_in),
				  buffer, USBTMC_SIZE_IOBUFFER,
				  &actual, USBTMC_TIMEOUT);

		n++;

		if (rv < 0) {
			dev_err(dev, "usb_bulk_msg returned %d\n", rv);
			goto exit;
		}
	} while ((actual == max_size) &&
		 (n < USBTMC_MAX_READS_TO_CLEAR_BULK_IN));

	if (actual == max_size) {
		dev_err(dev, "Couldn't clear device buffer within %d cycles\n",
			USBTMC_MAX_READS_TO_CLEAR_BULK_IN);
		rv = -EPERM;
		goto exit;
	}

	n = 0;

usbtmc_abort_bulk_in_status:
	rv = usb_control_msg(data->usb_dev,
			     usb_rcvctrlpipe(data->usb_dev, 0),
			     USBTMC_REQUEST_CHECK_ABORT_BULK_IN_STATUS,
			     USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_ENDPOINT,
			     0, data->bulk_in, buffer, 0x08,
			     USBTMC_TIMEOUT);

	if (rv < 0) {
		dev_err(dev, "usb_control_msg returned %d\n", rv);
		goto exit;
	}

	dev_dbg(dev, "INITIATE_ABORT_BULK_IN returned %x\n", buffer[0]);

	if (buffer[0] == USBTMC_STATUS_SUCCESS) {
		rv = 0;
		goto exit;
	}

	if (buffer[0] != USBTMC_STATUS_PENDING) {
		dev_err(dev, "INITIATE_ABORT_BULK_IN returned %x\n", buffer[0]);
		rv = -EPERM;
		goto exit;
	}

	if (buffer[1] == 1)
		do {
			dev_dbg(dev, "Reading from bulk in EP\n");

			rv = usb_bulk_msg(data->usb_dev,
					  usb_rcvbulkpipe(data->usb_dev,
							  data->bulk_in),
					  buffer, USBTMC_SIZE_IOBUFFER,
					  &actual, USBTMC_TIMEOUT);

			n++;

			if (rv < 0) {
				dev_err(dev, "usb_bulk_msg returned %d\n", rv);
				goto exit;
			}
		} while ((actual = max_size) &&
			 (n < USBTMC_MAX_READS_TO_CLEAR_BULK_IN));

	if (actual == max_size) {
		dev_err(dev, "Couldn't clear device buffer within %d cycles\n",
			USBTMC_MAX_READS_TO_CLEAR_BULK_IN);
		rv = -EPERM;
		goto exit;
	}

	goto usbtmc_abort_bulk_in_status;

exit:
	kfree(buffer);
	return rv;

}