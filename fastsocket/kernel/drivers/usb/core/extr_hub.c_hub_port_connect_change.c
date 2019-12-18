#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct usb_hub {int mA_per_port; struct usb_device* hdev; int /*<<< orphan*/  leds; int /*<<< orphan*/ * indicator; scalar_t__ has_indicators; int /*<<< orphan*/  removed_bits; int /*<<< orphan*/  change_bits; TYPE_2__* descriptor; struct device* intfdev; } ;
struct usb_hcd {TYPE_1__* driver; } ;
struct TYPE_8__ {scalar_t__ bDeviceClass; int /*<<< orphan*/  bcdUSB; } ;
struct device {int dummy; } ;
struct usb_device {scalar_t__ state; int bus_mA; scalar_t__ speed; scalar_t__ devnum; scalar_t__ parent; struct usb_device** children; TYPE_3__ descriptor; struct device dev; int /*<<< orphan*/  wusb; scalar_t__ level; TYPE_4__* bus; scalar_t__ persist_enabled; } ;
struct TYPE_9__ {scalar_t__ is_b_host; } ;
struct TYPE_7__ {int /*<<< orphan*/  wHubCharacteristics; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* relinquish_port ) (struct usb_hcd*,int) ;int /*<<< orphan*/  (* port_handed_over ) (struct usb_hcd*,int) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int ENOTCONN ; 
 int ENOTSUPP ; 
 unsigned int HUB_CHAR_LPSM ; 
 int /*<<< orphan*/  HUB_LED_AUTO ; 
 int /*<<< orphan*/  INDICATOR_AMBER_BLINK ; 
 int /*<<< orphan*/  INDICATOR_AUTO ; 
 int SET_CONFIG_TRIES ; 
 scalar_t__ USB_CLASS_HUB ; 
 int USB_DEVICE_SELF_POWERED ; 
 int /*<<< orphan*/  USB_PORT_FEAT_POWER ; 
 int USB_PORT_STAT_CONNECTION ; 
 int USB_PORT_STAT_C_CONNECTION ; 
 int USB_PORT_STAT_C_ENABLE ; 
 int USB_PORT_STAT_ENABLE ; 
 int /*<<< orphan*/  USB_RECIP_DEVICE ; 
 scalar_t__ USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_SUPER ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 scalar_t__ USB_STATE_NOTATTACHED ; 
 int /*<<< orphan*/  USB_STATE_POWERED ; 
 scalar_t__ USB_STATE_SUSPENDED ; 
 struct usb_hcd* bus_to_hcd (TYPE_4__*) ; 
 int /*<<< orphan*/  check_highspeed (struct usb_hub*,struct usb_device*,int) ; 
 int /*<<< orphan*/  choose_devnum (struct usb_device*) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  device_state_lock ; 
 scalar_t__ highspeed_hubs ; 
 int /*<<< orphan*/  hub_free_dev (struct usb_device*) ; 
 scalar_t__ hub_is_superspeed (struct usb_device*) ; 
 int /*<<< orphan*/  hub_is_wusb (struct usb_hub*) ; 
 int hub_port_debounce (struct usb_hub*,int) ; 
 int /*<<< orphan*/  hub_port_disable (struct usb_hub*,int,int) ; 
 int hub_port_init (struct usb_hub*,struct usb_device*,int,int) ; 
 int hub_power_remaining (struct usb_hub*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpus (int*) ; 
 int /*<<< orphan*/  port_is_power_on (struct usb_hub*,int) ; 
 int /*<<< orphan*/  portspeed (struct usb_hub*,int) ; 
 scalar_t__ printk_ratelimit () ; 
 int /*<<< orphan*/  release_devnum (struct usb_device*) ; 
 int remote_wakeup (struct usb_device*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_port_feature (struct usb_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_port_led (struct usb_hub*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct usb_hcd*,int) ; 
 int /*<<< orphan*/  stub2 (struct usb_hcd*,int) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 
 struct usb_device* usb_alloc_dev (struct usb_device*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  usb_disconnect (struct usb_device**) ; 
 int /*<<< orphan*/  usb_ep0_reinit (struct usb_device*) ; 
 int usb_get_status (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  usb_lock_device (struct usb_device*) ; 
 int usb_new_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_device_state (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unlock_device (struct usb_device*) ; 

__attribute__((used)) static void hub_port_connect_change(struct usb_hub *hub, int port1,
					u16 portstatus, u16 portchange)
{
	struct usb_device *hdev = hub->hdev;
	struct device *hub_dev = hub->intfdev;
	struct usb_hcd *hcd = bus_to_hcd(hdev->bus);
	unsigned wHubCharacteristics =
			le16_to_cpu(hub->descriptor->wHubCharacteristics);
	struct usb_device *udev;
	int status, i;

	dev_dbg (hub_dev,
		"port %d, status %04x, change %04x, %s\n",
		port1, portstatus, portchange, portspeed(hub, portstatus));

	if (hub->has_indicators) {
		set_port_led(hub, port1, HUB_LED_AUTO);
		hub->indicator[port1-1] = INDICATOR_AUTO;
	}

#ifdef	CONFIG_USB_OTG
	/* during HNP, don't repeat the debounce */
	if (hdev->bus->is_b_host)
		portchange &= ~(USB_PORT_STAT_C_CONNECTION |
				USB_PORT_STAT_C_ENABLE);
#endif

	/* Try to resuscitate an existing device */
	udev = hdev->children[port1-1];
	if ((portstatus & USB_PORT_STAT_CONNECTION) && udev &&
			udev->state != USB_STATE_NOTATTACHED) {
		usb_lock_device(udev);
		if (portstatus & USB_PORT_STAT_ENABLE) {
			status = 0;		/* Nothing to do */

#ifdef CONFIG_USB_SUSPEND
		} else if (udev->state == USB_STATE_SUSPENDED &&
				udev->persist_enabled) {
			/* For a suspended device, treat this as a
			 * remote wakeup event.
			 */
			status = remote_wakeup(udev);
#endif

		} else {
			status = -ENODEV;	/* Don't resuscitate */
		}
		usb_unlock_device(udev);

		if (status == 0) {
			clear_bit(port1, hub->change_bits);
			return;
		}
	}

	/* Disconnect any existing devices under this port */
	if (udev)
		usb_disconnect(&hdev->children[port1-1]);
	clear_bit(port1, hub->change_bits);

	/* We can forget about a "removed" device when there's a physical
	 * disconnect or the connect status changes.
	 */
	if (!(portstatus & USB_PORT_STAT_CONNECTION) ||
			(portchange & USB_PORT_STAT_C_CONNECTION))
		clear_bit(port1, hub->removed_bits);

	if (portchange & (USB_PORT_STAT_C_CONNECTION |
				USB_PORT_STAT_C_ENABLE)) {
		status = hub_port_debounce(hub, port1);
		if (status < 0) {
			if (printk_ratelimit())
				dev_err(hub_dev, "connect-debounce failed, "
						"port %d disabled\n", port1);
			portstatus &= ~USB_PORT_STAT_CONNECTION;
		} else {
			portstatus = status;
		}
	}

	/* Return now if debouncing failed or nothing is connected or
	 * the device was "removed".
	 */
	if (!(portstatus & USB_PORT_STAT_CONNECTION) ||
			test_bit(port1, hub->removed_bits)) {

		/* maybe switch power back on (e.g. root hub was reset) */
		if ((wHubCharacteristics & HUB_CHAR_LPSM) < 2
				&& !port_is_power_on(hub, portstatus))
			set_port_feature(hdev, port1, USB_PORT_FEAT_POWER);

		if (portstatus & USB_PORT_STAT_ENABLE)
  			goto done;
		return;
	}

	for (i = 0; i < SET_CONFIG_TRIES; i++) {

		/* reallocate for each attempt, since references
		 * to the previous one can escape in various ways
		 */
		udev = usb_alloc_dev(hdev, hdev->bus, port1);
		if (!udev) {
			dev_err (hub_dev,
				"couldn't allocate port %d usb_device\n",
				port1);
			goto done;
		}

		usb_set_device_state(udev, USB_STATE_POWERED);
 		udev->bus_mA = hub->mA_per_port;
		udev->level = hdev->level + 1;
		udev->wusb = hub_is_wusb(hub);

		/* Only USB 3.0 devices are connected to SuperSpeed hubs. */
		if (hub_is_superspeed(hub->hdev))
			udev->speed = USB_SPEED_SUPER;
		else
			udev->speed = USB_SPEED_UNKNOWN;

		choose_devnum(udev);
		if (udev->devnum <= 0) {
			status = -ENOTCONN;	/* Don't retry */
			goto loop;
		}

		/* reset (non-USB 3.0 devices) and get descriptor */
		status = hub_port_init(hub, udev, port1, i);
		if (status < 0)
			goto loop;

		/* consecutive bus-powered hubs aren't reliable; they can
		 * violate the voltage drop budget.  if the new child has
		 * a "powered" LED, users should notice we didn't enable it
		 * (without reading syslog), even without per-port LEDs
		 * on the parent.
		 */
		if (udev->descriptor.bDeviceClass == USB_CLASS_HUB
				&& udev->bus_mA <= 100) {
			u16	devstat;

			status = usb_get_status(udev, USB_RECIP_DEVICE, 0,
					&devstat);
			if (status < 2) {
				dev_dbg(&udev->dev, "get status %d ?\n", status);
				goto loop_disable;
			}
			le16_to_cpus(&devstat);
			if ((devstat & (1 << USB_DEVICE_SELF_POWERED)) == 0) {
				dev_err(&udev->dev,
					"can't connect bus-powered hub "
					"to this port\n");
				if (hub->has_indicators) {
					hub->indicator[port1-1] =
						INDICATOR_AMBER_BLINK;
					schedule_delayed_work (&hub->leds, 0);
				}
				status = -ENOTCONN;	/* Don't retry */
				goto loop_disable;
			}
		}
 
		/* check for devices running slower than they could */
		if (le16_to_cpu(udev->descriptor.bcdUSB) >= 0x0200
				&& udev->speed == USB_SPEED_FULL
				&& highspeed_hubs != 0)
			check_highspeed (hub, udev, port1);

		/* Store the parent's children[] pointer.  At this point
		 * udev becomes globally accessible, although presumably
		 * no one will look at it until hdev is unlocked.
		 */
		status = 0;

		/* We mustn't add new devices if the parent hub has
		 * been disconnected; we would race with the
		 * recursively_mark_NOTATTACHED() routine.
		 */
		spin_lock_irq(&device_state_lock);
		if (hdev->state == USB_STATE_NOTATTACHED)
			status = -ENOTCONN;
		else
			hdev->children[port1-1] = udev;
		spin_unlock_irq(&device_state_lock);

		/* Run it through the hoops (find a driver, etc) */
		if (!status) {
			status = usb_new_device(udev);
			if (status) {
				spin_lock_irq(&device_state_lock);
				hdev->children[port1-1] = NULL;
				spin_unlock_irq(&device_state_lock);
			}
		}

		if (status)
			goto loop_disable;

		status = hub_power_remaining(hub);
		if (status)
			dev_dbg(hub_dev, "%dmA power budget left\n", status);

		return;

loop_disable:
		hub_port_disable(hub, port1, 1);
loop:
		usb_ep0_reinit(udev);
		release_devnum(udev);
		hub_free_dev(udev);
		usb_put_dev(udev);
		if ((status == -ENOTCONN) || (status == -ENOTSUPP))
			break;
	}
	if (hub->hdev->parent ||
			!hcd->driver->port_handed_over ||
			!(hcd->driver->port_handed_over)(hcd, port1))
		dev_err(hub_dev, "unable to enumerate USB device on port %d\n",
				port1);
 
done:
	hub_port_disable(hub, port1, 1);
	if (hcd->driver->relinquish_port && !hub->hdev->parent)
		hcd->driver->relinquish_port(hcd, port1);
}