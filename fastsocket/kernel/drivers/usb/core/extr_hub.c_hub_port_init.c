#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct usb_hub {int /*<<< orphan*/  tt; struct usb_device* hdev; } ;
struct usb_hcd {TYPE_2__* driver; } ;
struct usb_device_descriptor {int bMaxPacketSize0; int bDescriptorType; } ;
struct TYPE_8__ {int bMaxPacketSize0; void* bcdUSB; } ;
struct TYPE_10__ {void* wMaxPacketSize; } ;
struct TYPE_11__ {TYPE_3__ desc; } ;
struct usb_device {int speed; int devnum; int ttport; scalar_t__ wusb; int /*<<< orphan*/  lpm_capable; TYPE_1__ descriptor; int /*<<< orphan*/  dev; TYPE_4__ ep0; TYPE_7__* bus; scalar_t__ config; int /*<<< orphan*/ * tt; int /*<<< orphan*/  parent; } ;
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;
struct TYPE_14__ {int otg_port; TYPE_6__* controller; scalar_t__ b_hnp_enable; } ;
struct TYPE_13__ {TYPE_5__* driver; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int flags; int /*<<< orphan*/  (* update_device ) (struct usb_hcd*,struct usb_device*) ;} ;
typedef  int /*<<< orphan*/  DEFINE_MUTEX ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOMSG ; 
 int EPROTO ; 
 int /*<<< orphan*/  GET_DESCRIPTOR_BUFSIZE ; 
 int GET_DESCRIPTOR_TRIES ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int HCD_USB3 ; 
 unsigned int HUB_BH_RESET_TIME ; 
 unsigned int HUB_LONG_RESET_TIME ; 
 unsigned int HUB_ROOT_RESET_TIME ; 
 unsigned int HUB_SHORT_RESET_TIME ; 
 int SET_ADDRESS_TRIES ; 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int USB_DT_DEVICE ; 
 int USB_DT_DEVICE_SIZE ; 
 int /*<<< orphan*/  USB_REQ_GET_DESCRIPTOR ; 
#define  USB_SPEED_FULL 132 
#define  USB_SPEED_HIGH 131 
#define  USB_SPEED_LOW 130 
#define  USB_SPEED_SUPER 129 
 int USB_SPEED_UNKNOWN ; 
#define  USB_SPEED_WIRELESS 128 
 scalar_t__ USE_NEW_SCHEME (int) ; 
 struct usb_hcd* bus_to_hcd (TYPE_7__*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  hub_port_disable (struct usb_hub*,int,int /*<<< orphan*/ ) ; 
 int hub_port_reset (struct usb_hub*,int,struct usb_device*,unsigned int,int) ; 
 int hub_set_address (struct usb_device*,int) ; 
 int /*<<< orphan*/  initial_descriptor_timeout ; 
 int /*<<< orphan*/  kfree (struct usb_device_descriptor*) ; 
 struct usb_device_descriptor* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (void*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct usb_hcd*,struct usb_device*) ; 
 int /*<<< orphan*/  update_devnum (struct usb_device*,int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct usb_device_descriptor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_device_supports_lpm (struct usb_device*) ; 
 int /*<<< orphan*/  usb_ep0_reinit (struct usb_device*) ; 
 int usb_get_bos_descriptor (struct usb_device*) ; 
 int usb_get_device_descriptor (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_rcvaddr0pipe () ; 
 int /*<<< orphan*/  usb_set_lpm_parameters (struct usb_device*) ; 

__attribute__((used)) static int
hub_port_init (struct usb_hub *hub, struct usb_device *udev, int port1,
		int retry_counter)
{
	static DEFINE_MUTEX(usb_address0_mutex);

	struct usb_device	*hdev = hub->hdev;
	struct usb_hcd		*hcd = bus_to_hcd(hdev->bus);
	int			i, j, retval;
	unsigned		delay = HUB_SHORT_RESET_TIME;
	enum usb_device_speed	oldspeed = udev->speed;
	char 			*speed, *type;
	int			devnum = udev->devnum;

	/* root hub ports have a slightly longer reset period
	 * (from USB 2.0 spec, section 7.1.7.5)
	 */
	if (!hdev->parent) {
		delay = HUB_ROOT_RESET_TIME;
		if (port1 == hdev->bus->otg_port)
			hdev->bus->b_hnp_enable = 0;
	}

	/* Some low speed devices have problems with the quick delay, so */
	/*  be a bit pessimistic with those devices. RHbug #23670 */
	if (oldspeed == USB_SPEED_LOW)
		delay = HUB_LONG_RESET_TIME;

	mutex_lock(&usb_address0_mutex);

	/* Reset the device; full speed may morph to high speed */
	/* FIXME a USB 2.0 device may morph into SuperSpeed on reset. */
	retval = hub_port_reset(hub, port1, udev, delay, false);
	if (retval < 0)		/* error or disconnect */
		goto fail;
	/* success, speed is known */

	retval = -ENODEV;

	if (oldspeed != USB_SPEED_UNKNOWN && oldspeed != udev->speed) {
		dev_dbg(&udev->dev, "device reset changed speed!\n");
		goto fail;
	}
	oldspeed = udev->speed;

	/* USB 2.0 section 5.5.3 talks about ep0 maxpacket ...
	 * it's fixed size except for full speed devices.
	 * For Wireless USB devices, ep0 max packet is always 512 (tho
	 * reported as 0xff in the device descriptor). WUSB1.0[4.8.1].
	 */
	switch (udev->speed) {
	case USB_SPEED_SUPER:
	case USB_SPEED_WIRELESS:	/* fixed at 512 */
		udev->ep0.desc.wMaxPacketSize = cpu_to_le16(512);
		break;
	case USB_SPEED_HIGH:		/* fixed at 64 */
		udev->ep0.desc.wMaxPacketSize = cpu_to_le16(64);
		break;
	case USB_SPEED_FULL:		/* 8, 16, 32, or 64 */
		/* to determine the ep0 maxpacket size, try to read
		 * the device descriptor to get bMaxPacketSize0 and
		 * then correct our initial guess.
		 */
		udev->ep0.desc.wMaxPacketSize = cpu_to_le16(64);
		break;
	case USB_SPEED_LOW:		/* fixed at 8 */
		udev->ep0.desc.wMaxPacketSize = cpu_to_le16(8);
		break;
	default:
		goto fail;
	}
 
	type = "";
	switch (udev->speed) {
	case USB_SPEED_LOW:	speed = "low";	break;
	case USB_SPEED_FULL:	speed = "full";	break;
	case USB_SPEED_HIGH:	speed = "high";	break;
	case USB_SPEED_SUPER:
				speed = "super";
				break;
	case USB_SPEED_WIRELESS:
				speed = "variable";
				type = "Wireless ";
				break;
	default: 		speed = "?";	break;
	}
	if (udev->speed != USB_SPEED_SUPER)
		dev_info(&udev->dev,
				"%s %s speed %sUSB device number %d using %s\n",
				(udev->config) ? "reset" : "new", speed, type,
				devnum, udev->bus->controller->driver->name);

	/* Set up TT records, if needed  */
	if (hdev->tt) {
		udev->tt = hdev->tt;
		udev->ttport = hdev->ttport;
	} else if (udev->speed != USB_SPEED_HIGH
			&& hdev->speed == USB_SPEED_HIGH) {
		udev->tt = &hub->tt;
		udev->ttport = port1;
	}
 
	/* Why interleave GET_DESCRIPTOR and SET_ADDRESS this way?
	 * Because device hardware and firmware is sometimes buggy in
	 * this area, and this is how Linux has done it for ages.
	 * Change it cautiously.
	 *
	 * NOTE:  If USE_NEW_SCHEME() is true we will start by issuing
	 * a 64-byte GET_DESCRIPTOR request.  This is what Windows does,
	 * so it may help with some non-standards-compliant devices.
	 * Otherwise we start with SET_ADDRESS and then try to read the
	 * first 8 bytes of the device descriptor to get the ep0 maxpacket
	 * value.
	 */
	for (i = 0; i < GET_DESCRIPTOR_TRIES; (++i, msleep(100))) {
		if (USE_NEW_SCHEME(retry_counter) && !(hcd->driver->flags & HCD_USB3)) {
			struct usb_device_descriptor *buf;
			int r = 0;

#define GET_DESCRIPTOR_BUFSIZE	64
			buf = kmalloc(GET_DESCRIPTOR_BUFSIZE, GFP_NOIO);
			if (!buf) {
				retval = -ENOMEM;
				continue;
			}

			/* Retry on all errors; some devices are flakey.
			 * 255 is for WUSB devices, we actually need to use
			 * 512 (WUSB1.0[4.8.1]).
			 */
			for (j = 0; j < 3; ++j) {
				buf->bMaxPacketSize0 = 0;
				r = usb_control_msg(udev, usb_rcvaddr0pipe(),
					USB_REQ_GET_DESCRIPTOR, USB_DIR_IN,
					USB_DT_DEVICE << 8, 0,
					buf, GET_DESCRIPTOR_BUFSIZE,
					initial_descriptor_timeout);
				switch (buf->bMaxPacketSize0) {
				case 8: case 16: case 32: case 64: case 255:
					if (buf->bDescriptorType ==
							USB_DT_DEVICE) {
						r = 0;
						break;
					}
					/* FALL THROUGH */
				default:
					if (r == 0)
						r = -EPROTO;
					break;
				}
				if (r == 0)
					break;
			}
			udev->descriptor.bMaxPacketSize0 =
					buf->bMaxPacketSize0;
			kfree(buf);

			retval = hub_port_reset(hub, port1, udev, delay, false);
			if (retval < 0)		/* error or disconnect */
				goto fail;
			if (oldspeed != udev->speed) {
				dev_dbg(&udev->dev,
					"device reset changed speed!\n");
				retval = -ENODEV;
				goto fail;
			}
			if (r) {
				dev_err(&udev->dev,
					"device descriptor read/64, error %d\n",
					r);
				retval = -EMSGSIZE;
				continue;
			}
#undef GET_DESCRIPTOR_BUFSIZE
		}

 		/*
 		 * If device is WUSB, we already assigned an
 		 * unauthorized address in the Connect Ack sequence;
 		 * authorization will assign the final address.
 		 */
		if (udev->wusb == 0) {
			for (j = 0; j < SET_ADDRESS_TRIES; ++j) {
				retval = hub_set_address(udev, devnum);
				if (retval >= 0)
					break;
				msleep(200);
			}
			if (retval < 0) {
				dev_err(&udev->dev,
					"device not accepting address %d, error %d\n",
					devnum, retval);
				goto fail;
			}
			if (udev->speed == USB_SPEED_SUPER) {
				devnum = udev->devnum;
				dev_info(&udev->dev,
						"%s SuperSpeed USB device number %d using %s\n",
						(udev->config) ? "reset" : "new",
						devnum, udev->bus->controller->driver->name);
			}

			/* cope with hardware quirkiness:
			 *  - let SET_ADDRESS settle, some device hardware wants it
			 *  - read ep0 maxpacket even for high and low speed,
			 */
			msleep(10);
			if (USE_NEW_SCHEME(retry_counter) && !(hcd->driver->flags & HCD_USB3))
				break;
  		}

		retval = usb_get_device_descriptor(udev, 8);
		if (retval < 8) {
			dev_err(&udev->dev,
					"device descriptor read/8, error %d\n",
					retval);
			if (retval >= 0)
				retval = -EMSGSIZE;
		} else {
			retval = 0;
			break;
		}
	}
	if (retval)
		goto fail;

	/*
	 * Some superspeed devices have finished the link training process
	 * and attached to a superspeed hub port, but the device descriptor
	 * got from those devices show they aren't superspeed devices. Warm
	 * reset the port attached by the devices can fix them.
	 */
	if ((udev->speed == USB_SPEED_SUPER) &&
			(le16_to_cpu(udev->descriptor.bcdUSB) < 0x0300)) {
		dev_err(&udev->dev, "got a wrong device descriptor, "
				"warm reset device\n");
		hub_port_reset(hub, port1, udev,
				HUB_BH_RESET_TIME, true);
		retval = -EINVAL;
		goto fail;
	}

	if (udev->descriptor.bMaxPacketSize0 == 0xff ||
			udev->speed == USB_SPEED_SUPER)
		i = 512;
	else
		i = udev->descriptor.bMaxPacketSize0;
	if (le16_to_cpu(udev->ep0.desc.wMaxPacketSize) != i) {
		if (udev->speed != USB_SPEED_FULL ||
				!(i == 8 || i == 16 || i == 32 || i == 64)) {
			dev_err(&udev->dev, "ep0 maxpacket = %d\n", i);
			retval = -EMSGSIZE;
			goto fail;
		}
		dev_dbg(&udev->dev, "ep0 maxpacket = %d\n", i);
		udev->ep0.desc.wMaxPacketSize = cpu_to_le16(i);
		usb_ep0_reinit(udev);
	}
  
	retval = usb_get_device_descriptor(udev, USB_DT_DEVICE_SIZE);
	if (retval < (signed)sizeof(udev->descriptor)) {
		dev_err(&udev->dev, "device descriptor read/all, error %d\n",
			retval);
		if (retval >= 0)
			retval = -ENOMSG;
		goto fail;
	}

	if (udev->wusb == 0 && le16_to_cpu(udev->descriptor.bcdUSB) >= 0x0201) {
		retval = usb_get_bos_descriptor(udev);
		if (!retval) {
			udev->lpm_capable = usb_device_supports_lpm(udev);
			usb_set_lpm_parameters(udev);
		}
	}

	retval = 0;
	/* notify HCD that we have a device connected and addressed */
	if (hcd->driver->update_device)
		hcd->driver->update_device(hcd, udev);
fail:
	if (retval) {
		hub_port_disable(hub, port1, 0);
		update_devnum(udev, devnum);	/* for disconnect processing */
	}
	mutex_unlock(&usb_address0_mutex);
	return retval;
}