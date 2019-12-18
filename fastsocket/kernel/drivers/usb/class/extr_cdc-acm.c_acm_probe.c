#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
struct usb_interface {int /*<<< orphan*/  dev; TYPE_4__* cur_altsetting; TYPE_1__* altsetting; } ;
struct usb_endpoint_descriptor {int bInterval; int /*<<< orphan*/  bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; } ;
struct usb_device_id {scalar_t__ driver_info; } ;
struct usb_device {int dummy; } ;
struct usb_cdc_union_desc {int bMasterInterface0; int bSlaveInterface0; } ;
struct usb_cdc_country_functional_desc {int /*<<< orphan*/  iCountryCodeRelDate; scalar_t__ bLength; int /*<<< orphan*/  wCountyCode0; } ;
struct TYPE_11__ {int bDataBits; int /*<<< orphan*/  dwDTERate; } ;
struct TYPE_18__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_16__ {unsigned long data; int /*<<< orphan*/  func; } ;
struct acm_wb {int combined_interfaces; int writesize; int minor; int ctrl_caps; int ctrlsize; int readsize; int rx_buflimit; int bInterval; int* ctrl_buffer; int /*<<< orphan*/  ctrl_dma; TYPE_6__* ctrlurb; struct acm_ru* ru; TYPE_6__* urb; struct acm_wb* wb; TYPE_10__ line; int /*<<< orphan*/  ctrlout; struct acm_wb* country_codes; int /*<<< orphan*/  country_rel_date; scalar_t__ country_code_size; struct acm_wb* instance; struct usb_device* dev; struct acm_rb* rb; TYPE_9__ port; scalar_t__ is_int_ep; int /*<<< orphan*/  rx_endpoint; int /*<<< orphan*/  mutex; int /*<<< orphan*/  read_lock; int /*<<< orphan*/  write_lock; int /*<<< orphan*/  throttle_lock; int /*<<< orphan*/  drain_wait; int /*<<< orphan*/  work; TYPE_5__ urb_task; struct usb_interface* data; struct usb_interface* control; } ;
struct acm_ru {TYPE_6__* urb; struct acm_wb* instance; } ;
struct acm_rb {void* base; int /*<<< orphan*/  dma; } ;
struct acm {int combined_interfaces; int writesize; int minor; int ctrl_caps; int ctrlsize; int readsize; int rx_buflimit; int bInterval; int* ctrl_buffer; int /*<<< orphan*/  ctrl_dma; TYPE_6__* ctrlurb; struct acm_ru* ru; TYPE_6__* urb; struct acm* wb; TYPE_10__ line; int /*<<< orphan*/  ctrlout; struct acm* country_codes; int /*<<< orphan*/  country_rel_date; scalar_t__ country_code_size; struct acm* instance; struct usb_device* dev; struct acm_rb* rb; TYPE_9__ port; scalar_t__ is_int_ep; int /*<<< orphan*/  rx_endpoint; int /*<<< orphan*/  mutex; int /*<<< orphan*/  read_lock; int /*<<< orphan*/  write_lock; int /*<<< orphan*/  throttle_lock; int /*<<< orphan*/  drain_wait; int /*<<< orphan*/  work; TYPE_5__ urb_task; struct usb_interface* data; struct usb_interface* control; } ;
struct TYPE_17__ {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_flags; } ;
struct TYPE_13__ {int bNumEndpoints; scalar_t__ bInterfaceClass; } ;
struct TYPE_15__ {TYPE_3__* endpoint; TYPE_2__ desc; } ;
struct TYPE_14__ {int extralen; unsigned char* extra; struct usb_endpoint_descriptor desc; } ;
struct TYPE_12__ {unsigned char* extra; int extralen; } ;

/* Variables and functions */
 int ACM_NR ; 
 int ACM_NW ; 
 int ACM_TTY_MINORS ; 
 scalar_t__ CDC_DATA_INTERFACE_TYPE ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long NO_CAP_LINE ; 
 unsigned long NO_UNION_NORMAL ; 
 unsigned long SINGLE_RX_URB ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
#define  USB_CDC_ACM_TYPE 132 
#define  USB_CDC_CALL_MANAGEMENT_TYPE 131 
 int USB_CDC_CAP_LINE ; 
#define  USB_CDC_COUNTRY_TYPE 130 
#define  USB_CDC_HEADER_TYPE 129 
#define  USB_CDC_UNION_TYPE 128 
 unsigned char USB_DT_CS_INTERFACE ; 
 int /*<<< orphan*/  acm_ctrl_irq ; 
 int /*<<< orphan*/  acm_driver ; 
 int /*<<< orphan*/  acm_port_ops ; 
 int /*<<< orphan*/  acm_read_buffers_free (struct acm_wb*) ; 
 int /*<<< orphan*/  acm_rx_tasklet ; 
 int /*<<< orphan*/  acm_set_control (struct acm_wb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acm_set_line (struct acm_wb*,TYPE_10__*) ; 
 int /*<<< orphan*/  acm_softint ; 
 struct acm_wb** acm_table ; 
 int /*<<< orphan*/  acm_tty_driver ; 
 scalar_t__ acm_write_buffers_alloc (struct acm_wb*) ; 
 int /*<<< orphan*/  acm_write_buffers_free (struct acm_wb*) ; 
 int /*<<< orphan*/  acm_write_bulk ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  dev_attr_bmCapabilities ; 
 int /*<<< orphan*/  dev_attr_iCountryCodeRelDate ; 
 int /*<<< orphan*/  dev_attr_wCountryCodes ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct acm_wb*) ; 
 struct acm_wb* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 struct acm_wb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct acm_wb*,int*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_init (TYPE_9__*) ; 
 int /*<<< orphan*/  tty_register_device (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* usb_buffer_alloc (struct usb_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_buffer_free (struct usb_device*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_driver_claim_interface (int /*<<< orphan*/ *,struct usb_interface*,struct acm_wb*) ; 
 int /*<<< orphan*/  usb_endpoint_dir_in (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_is_bulk_in (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_is_bulk_out (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_is_int_in (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_xfer_int (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_6__*,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct acm_wb*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_6__*,struct usb_device*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,struct acm_wb*,int) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_6__*) ; 
 int /*<<< orphan*/  usb_get_intf (struct usb_interface*) ; 
 struct usb_interface* usb_ifnum_to_if (struct usb_device*,int) ; 
 scalar_t__ usb_interface_claimed (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct acm_wb*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acm_probe(struct usb_interface *intf,
		     const struct usb_device_id *id)
{
	struct usb_cdc_union_desc *union_header = NULL;
	struct usb_cdc_country_functional_desc *cfd = NULL;
	unsigned char *buffer = intf->altsetting->extra;
	int buflen = intf->altsetting->extralen;
	struct usb_interface *control_interface;
	struct usb_interface *data_interface;
	struct usb_endpoint_descriptor *epctrl = NULL;
	struct usb_endpoint_descriptor *epread = NULL;
	struct usb_endpoint_descriptor *epwrite = NULL;
	struct usb_device *usb_dev = interface_to_usbdev(intf);
	struct acm *acm;
	int minor;
	int ctrlsize, readsize;
	u8 *buf;
	u8 ac_management_function = 0;
	u8 call_management_function = 0;
	int call_interface_num = -1;
	int data_interface_num;
	unsigned long quirks;
	int num_rx_buf;
	int i;
	int combined_interfaces = 0;

	/* normal quirks */
	quirks = (unsigned long)id->driver_info;
	num_rx_buf = (quirks == SINGLE_RX_URB) ? 1 : ACM_NR;

	/* handle quirks deadly to normal probing*/
	if (quirks == NO_UNION_NORMAL) {
		data_interface = usb_ifnum_to_if(usb_dev, 1);
		control_interface = usb_ifnum_to_if(usb_dev, 0);
		goto skip_normal_probe;
	}

	/* normal probing*/
	if (!buffer) {
		dev_err(&intf->dev, "Weird descriptor references\n");
		return -EINVAL;
	}

	if (!buflen) {
		if (intf->cur_altsetting->endpoint->extralen &&
				intf->cur_altsetting->endpoint->extra) {
			dev_dbg(&intf->dev,
				"Seeking extra descriptors on endpoint\n");
			buflen = intf->cur_altsetting->endpoint->extralen;
			buffer = intf->cur_altsetting->endpoint->extra;
		} else {
			dev_err(&intf->dev,
				"Zero length descriptor references\n");
			return -EINVAL;
		}
	}

	while (buflen > 0) {
		if (buffer[1] != USB_DT_CS_INTERFACE) {
			dev_err(&intf->dev, "skipping garbage\n");
			goto next_desc;
		}

		switch (buffer[2]) {
		case USB_CDC_UNION_TYPE: /* we've found it */
			if (union_header) {
				dev_err(&intf->dev, "More than one "
					"union descriptor, skipping ...\n");
				goto next_desc;
			}
			union_header = (struct usb_cdc_union_desc *)buffer;
			break;
		case USB_CDC_COUNTRY_TYPE: /* export through sysfs*/
			cfd = (struct usb_cdc_country_functional_desc *)buffer;
			break;
		case USB_CDC_HEADER_TYPE: /* maybe check version */
			break; /* for now we ignore it */
		case USB_CDC_ACM_TYPE:
			ac_management_function = buffer[3];
			break;
		case USB_CDC_CALL_MANAGEMENT_TYPE:
			call_management_function = buffer[3];
			call_interface_num = buffer[4];
			if ((call_management_function & 3) != 3)
				dev_err(&intf->dev, "This device cannot do calls on its own. It is not a modem.\n");
			break;
		default:
			/* there are LOTS more CDC descriptors that
			 * could legitimately be found here.
			 */
			dev_dbg(&intf->dev, "Ignoring descriptor: "
					"type %02x, length %d\n",
					buffer[2], buffer[0]);
			break;
		}
next_desc:
		buflen -= buffer[0];
		buffer += buffer[0];
	}

	if (!union_header) {
		if (call_interface_num > 0) {
			dev_dbg(&intf->dev, "No union descriptor, using call management descriptor\n");
			data_interface = usb_ifnum_to_if(usb_dev, (data_interface_num = call_interface_num));
			control_interface = intf;
		} else {
			if (intf->cur_altsetting->desc.bNumEndpoints != 3) {
				dev_dbg(&intf->dev,"No union descriptor, giving up\n");
				return -ENODEV;
			} else {
				dev_warn(&intf->dev,"No union descriptor, testing for castrated device\n");
				combined_interfaces = 1;
				control_interface = data_interface = intf;
				goto look_for_collapsed_interface;
			}
		}
	} else {
		control_interface = usb_ifnum_to_if(usb_dev, union_header->bMasterInterface0);
		data_interface = usb_ifnum_to_if(usb_dev, (data_interface_num = union_header->bSlaveInterface0));
		if (!control_interface || !data_interface) {
			dev_dbg(&intf->dev, "no interfaces\n");
			return -ENODEV;
		}
	}

	if (data_interface_num != call_interface_num)
		dev_dbg(&intf->dev, "Separate call control interface. That is not fully supported.\n");

	if (control_interface == data_interface) {
		/* some broken devices designed for windows work this way */
		dev_warn(&intf->dev,"Control and data interfaces are not separated!\n");
		combined_interfaces = 1;
		/* a popular other OS doesn't use it */
		quirks |= NO_CAP_LINE;
		if (data_interface->cur_altsetting->desc.bNumEndpoints != 3) {
			dev_err(&intf->dev, "This needs exactly 3 endpoints\n");
			return -EINVAL;
		}
look_for_collapsed_interface:
		for (i = 0; i < 3; i++) {
			struct usb_endpoint_descriptor *ep;
			ep = &data_interface->cur_altsetting->endpoint[i].desc;

			if (usb_endpoint_is_int_in(ep))
				epctrl = ep;
			else if (usb_endpoint_is_bulk_out(ep))
				epwrite = ep;
			else if (usb_endpoint_is_bulk_in(ep))
				epread = ep;
			else
				return -EINVAL;
		}
		if (!epctrl || !epread || !epwrite)
			return -ENODEV;
		else
			goto made_compressed_probe;
	}

skip_normal_probe:

	/*workaround for switched interfaces */
	if (data_interface->cur_altsetting->desc.bInterfaceClass
						!= CDC_DATA_INTERFACE_TYPE) {
		if (control_interface->cur_altsetting->desc.bInterfaceClass
						== CDC_DATA_INTERFACE_TYPE) {
			struct usb_interface *t;
			dev_dbg(&intf->dev,
				"Your device has switched interfaces.\n");
			t = control_interface;
			control_interface = data_interface;
			data_interface = t;
		} else {
			return -EINVAL;
		}
	}

	/* Accept probe requests only for the control interface */
	if (!combined_interfaces && intf != control_interface)
		return -ENODEV;

	if (!combined_interfaces && usb_interface_claimed(data_interface)) {
		/* valid in this context */
		dev_dbg(&intf->dev, "The data interface isn't available\n");
		return -EBUSY;
	}


	if (data_interface->cur_altsetting->desc.bNumEndpoints < 2)
		return -EINVAL;

	epctrl = &control_interface->cur_altsetting->endpoint[0].desc;
	epread = &data_interface->cur_altsetting->endpoint[0].desc;
	epwrite = &data_interface->cur_altsetting->endpoint[1].desc;


	/* workaround for switched endpoints */
	if (!usb_endpoint_dir_in(epread)) {
		/* descriptors are swapped */
		struct usb_endpoint_descriptor *t;
		dev_dbg(&intf->dev,
			"The data interface has switched endpoints\n");
		t = epread;
		epread = epwrite;
		epwrite = t;
	}
made_compressed_probe:
	dbg("interfaces are valid");
	for (minor = 0; minor < ACM_TTY_MINORS && acm_table[minor]; minor++);

	if (minor == ACM_TTY_MINORS) {
		dev_err(&intf->dev, "no more free acm devices\n");
		return -ENODEV;
	}

	acm = kzalloc(sizeof(struct acm), GFP_KERNEL);
	if (acm == NULL) {
		dev_dbg(&intf->dev, "out of memory (acm kzalloc)\n");
		goto alloc_fail;
	}

	ctrlsize = le16_to_cpu(epctrl->wMaxPacketSize);
	readsize = le16_to_cpu(epread->wMaxPacketSize) *
				(quirks == SINGLE_RX_URB ? 1 : 2);
	acm->combined_interfaces = combined_interfaces;
	acm->writesize = le16_to_cpu(epwrite->wMaxPacketSize) * 20;
	acm->control = control_interface;
	acm->data = data_interface;
	acm->minor = minor;
	acm->dev = usb_dev;
	acm->ctrl_caps = ac_management_function;
	if (quirks & NO_CAP_LINE)
		acm->ctrl_caps &= ~USB_CDC_CAP_LINE;
	acm->ctrlsize = ctrlsize;
	acm->readsize = readsize;
	acm->rx_buflimit = num_rx_buf;
	acm->urb_task.func = acm_rx_tasklet;
	acm->urb_task.data = (unsigned long) acm;
	INIT_WORK(&acm->work, acm_softint);
	init_waitqueue_head(&acm->drain_wait);
	spin_lock_init(&acm->throttle_lock);
	spin_lock_init(&acm->write_lock);
	spin_lock_init(&acm->read_lock);
	mutex_init(&acm->mutex);
	acm->rx_endpoint = usb_rcvbulkpipe(usb_dev, epread->bEndpointAddress);
	acm->is_int_ep = usb_endpoint_xfer_int(epread);
	if (acm->is_int_ep)
		acm->bInterval = epread->bInterval;
	tty_port_init(&acm->port);
	acm->port.ops = &acm_port_ops;

	buf = usb_buffer_alloc(usb_dev, ctrlsize, GFP_KERNEL, &acm->ctrl_dma);
	if (!buf) {
		dev_dbg(&intf->dev, "out of memory (ctrl buffer alloc)\n");
		goto alloc_fail2;
	}
	acm->ctrl_buffer = buf;

	if (acm_write_buffers_alloc(acm) < 0) {
		dev_dbg(&intf->dev, "out of memory (write buffer alloc)\n");
		goto alloc_fail4;
	}

	acm->ctrlurb = usb_alloc_urb(0, GFP_KERNEL);
	if (!acm->ctrlurb) {
		dev_dbg(&intf->dev, "out of memory (ctrlurb kmalloc)\n");
		goto alloc_fail5;
	}
	for (i = 0; i < num_rx_buf; i++) {
		struct acm_ru *rcv = &(acm->ru[i]);

		rcv->urb = usb_alloc_urb(0, GFP_KERNEL);
		if (rcv->urb == NULL) {
			dev_dbg(&intf->dev,
				"out of memory (read urbs usb_alloc_urb)\n");
			goto alloc_fail7;
		}

		rcv->urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		rcv->instance = acm;
	}
	for (i = 0; i < num_rx_buf; i++) {
		struct acm_rb *rb = &(acm->rb[i]);

		rb->base = usb_buffer_alloc(acm->dev, readsize,
				GFP_KERNEL, &rb->dma);
		if (!rb->base) {
			dev_dbg(&intf->dev,
				"out of memory (read bufs usb_buffer_alloc)\n");
			goto alloc_fail7;
		}
	}
	for (i = 0; i < ACM_NW; i++) {
		struct acm_wb *snd = &(acm->wb[i]);

		snd->urb = usb_alloc_urb(0, GFP_KERNEL);
		if (snd->urb == NULL) {
			dev_dbg(&intf->dev,
				"out of memory (write urbs usb_alloc_urb)");
			goto alloc_fail7;
		}

		if (usb_endpoint_xfer_int(epwrite))
			usb_fill_int_urb(snd->urb, usb_dev,
				usb_sndbulkpipe(usb_dev, epwrite->bEndpointAddress),
				NULL, acm->writesize, acm_write_bulk, snd, epwrite->bInterval);
		else
			usb_fill_bulk_urb(snd->urb, usb_dev,
				usb_sndbulkpipe(usb_dev, epwrite->bEndpointAddress),
				NULL, acm->writesize, acm_write_bulk, snd);
		snd->urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		snd->instance = acm;
	}

	usb_set_intfdata(intf, acm);

	i = device_create_file(&intf->dev, &dev_attr_bmCapabilities);
	if (i < 0)
		goto alloc_fail8;

	if (cfd) { /* export the country data */
		acm->country_codes = kmalloc(cfd->bLength - 4, GFP_KERNEL);
		if (!acm->country_codes)
			goto skip_countries;
		acm->country_code_size = cfd->bLength - 4;
		memcpy(acm->country_codes, (u8 *)&cfd->wCountyCode0,
							cfd->bLength - 4);
		acm->country_rel_date = cfd->iCountryCodeRelDate;

		i = device_create_file(&intf->dev, &dev_attr_wCountryCodes);
		if (i < 0) {
			kfree(acm->country_codes);
			goto skip_countries;
		}

		i = device_create_file(&intf->dev,
						&dev_attr_iCountryCodeRelDate);
		if (i < 0) {
			kfree(acm->country_codes);
			goto skip_countries;
		}
	}

skip_countries:
	usb_fill_int_urb(acm->ctrlurb, usb_dev,
			 usb_rcvintpipe(usb_dev, epctrl->bEndpointAddress),
			 acm->ctrl_buffer, ctrlsize, acm_ctrl_irq, acm,
			 /* works around buggy devices */
			 epctrl->bInterval ? epctrl->bInterval : 0xff);
	acm->ctrlurb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	acm->ctrlurb->transfer_dma = acm->ctrl_dma;

	dev_info(&intf->dev, "ttyACM%d: USB ACM device\n", minor);

	acm_set_control(acm, acm->ctrlout);

	acm->line.dwDTERate = cpu_to_le32(9600);
	acm->line.bDataBits = 8;
	acm_set_line(acm, &acm->line);

	usb_driver_claim_interface(&acm_driver, data_interface, acm);
	usb_set_intfdata(data_interface, acm);

	usb_get_intf(control_interface);
	tty_register_device(acm_tty_driver, minor, &control_interface->dev);

	acm_table[minor] = acm;

	return 0;
alloc_fail8:
	for (i = 0; i < ACM_NW; i++)
		usb_free_urb(acm->wb[i].urb);
alloc_fail7:
	acm_read_buffers_free(acm);
	for (i = 0; i < num_rx_buf; i++)
		usb_free_urb(acm->ru[i].urb);
	usb_free_urb(acm->ctrlurb);
alloc_fail5:
	acm_write_buffers_free(acm);
alloc_fail4:
	usb_buffer_free(usb_dev, ctrlsize, acm->ctrl_buffer, acm->ctrl_dma);
alloc_fail2:
	kfree(acm);
alloc_fail:
	return -ENOMEM;
}