#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; TYPE_2__* cur_altsetting; } ;
struct TYPE_6__ {int /*<<< orphan*/  wMaxPacketSize; int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_host_endpoint {TYPE_3__ desc; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct hci_dev {int /*<<< orphan*/  owner; int /*<<< orphan*/  ioctl; int /*<<< orphan*/  destruct; int /*<<< orphan*/  send; int /*<<< orphan*/  flush; int /*<<< orphan*/  close; int /*<<< orphan*/  open; struct bfusb_data* driver_data; int /*<<< orphan*/  type; } ;
struct firmware {struct usb_device_id const* size; struct usb_interface* data; } ;
struct bfusb_data {struct hci_dev* hdev; int /*<<< orphan*/  completed_q; int /*<<< orphan*/  pending_q; int /*<<< orphan*/  transmit_q; int /*<<< orphan*/ * reassembly; int /*<<< orphan*/  lock; int /*<<< orphan*/  bulk_pkt_size; int /*<<< orphan*/  bulk_out_ep; int /*<<< orphan*/  bulk_in_ep; struct usb_device* udev; } ;
struct TYPE_4__ {int bNumEndpoints; } ;
struct TYPE_5__ {struct usb_host_endpoint* endpoint; TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct usb_interface*,struct usb_device_id const*) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCI_USB ; 
 int /*<<< orphan*/  SET_HCIDEV_DEV (struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  bfusb_close ; 
 int /*<<< orphan*/  bfusb_destruct ; 
 int /*<<< orphan*/  bfusb_flush ; 
 int /*<<< orphan*/  bfusb_ioctl ; 
 scalar_t__ bfusb_load_firmware (struct bfusb_data*,struct usb_interface*,struct usb_device_id const*) ; 
 int /*<<< orphan*/  bfusb_open ; 
 int /*<<< orphan*/  bfusb_send_frame ; 
 struct hci_dev* hci_alloc_dev () ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 scalar_t__ hci_register_dev (struct hci_dev*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct bfusb_data*) ; 
 struct bfusb_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 scalar_t__ request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct bfusb_data*) ; 

__attribute__((used)) static int bfusb_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	const struct firmware *firmware;
	struct usb_device *udev = interface_to_usbdev(intf);
	struct usb_host_endpoint *bulk_out_ep;
	struct usb_host_endpoint *bulk_in_ep;
	struct hci_dev *hdev;
	struct bfusb_data *data;

	BT_DBG("intf %p id %p", intf, id);

	/* Check number of endpoints */
	if (intf->cur_altsetting->desc.bNumEndpoints < 2)
		return -EIO;

	bulk_out_ep = &intf->cur_altsetting->endpoint[0];
	bulk_in_ep  = &intf->cur_altsetting->endpoint[1];

	if (!bulk_out_ep || !bulk_in_ep) {
		BT_ERR("Bulk endpoints not found");
		goto done;
	}

	/* Initialize control structure and load firmware */
	data = kzalloc(sizeof(struct bfusb_data), GFP_KERNEL);
	if (!data) {
		BT_ERR("Can't allocate memory for control structure");
		goto done;
	}

	data->udev = udev;
	data->bulk_in_ep    = bulk_in_ep->desc.bEndpointAddress;
	data->bulk_out_ep   = bulk_out_ep->desc.bEndpointAddress;
	data->bulk_pkt_size = le16_to_cpu(bulk_out_ep->desc.wMaxPacketSize);

	rwlock_init(&data->lock);

	data->reassembly = NULL;

	skb_queue_head_init(&data->transmit_q);
	skb_queue_head_init(&data->pending_q);
	skb_queue_head_init(&data->completed_q);

	if (request_firmware(&firmware, "bfubase.frm", &udev->dev) < 0) {
		BT_ERR("Firmware request failed");
		goto error;
	}

	BT_DBG("firmware data %p size %zu", firmware->data, firmware->size);

	if (bfusb_load_firmware(data, firmware->data, firmware->size) < 0) {
		BT_ERR("Firmware loading failed");
		goto release;
	}

	release_firmware(firmware);

	/* Initialize and register HCI device */
	hdev = hci_alloc_dev();
	if (!hdev) {
		BT_ERR("Can't allocate HCI device");
		goto error;
	}

	data->hdev = hdev;

	hdev->type = HCI_USB;
	hdev->driver_data = data;
	SET_HCIDEV_DEV(hdev, &intf->dev);

	hdev->open     = bfusb_open;
	hdev->close    = bfusb_close;
	hdev->flush    = bfusb_flush;
	hdev->send     = bfusb_send_frame;
	hdev->destruct = bfusb_destruct;
	hdev->ioctl    = bfusb_ioctl;

	hdev->owner = THIS_MODULE;

	if (hci_register_dev(hdev) < 0) {
		BT_ERR("Can't register HCI device");
		hci_free_dev(hdev);
		goto error;
	}

	usb_set_intfdata(intf, data);

	return 0;

release:
	release_firmware(firmware);

error:
	kfree(data);

done:
	return -EIO;
}