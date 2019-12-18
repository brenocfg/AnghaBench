#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_hub {int dummy; } ;
struct usb_device {scalar_t__ speed; int /*<<< orphan*/  u2_params; int /*<<< orphan*/  u1_params; TYPE_5__* parent; TYPE_2__* bos; int /*<<< orphan*/  lpm_capable; } ;
struct TYPE_10__ {int /*<<< orphan*/  u2_params; int /*<<< orphan*/  u1_params; TYPE_4__* bos; } ;
struct TYPE_9__ {TYPE_3__* ss_cap; } ;
struct TYPE_8__ {unsigned int bU1devExitLat; unsigned int bU2DevExitLat; } ;
struct TYPE_7__ {TYPE_1__* ss_cap; } ;
struct TYPE_6__ {unsigned int bU1devExitLat; unsigned int bU2DevExitLat; } ;

/* Variables and functions */
 scalar_t__ USB_SPEED_SUPER ; 
 struct usb_hub* hdev_to_hub (TYPE_5__*) ; 
 int /*<<< orphan*/  usb_set_lpm_mel (struct usb_device*,int /*<<< orphan*/ *,unsigned int,struct usb_hub*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  usb_set_lpm_pel (struct usb_device*,int /*<<< orphan*/ *,unsigned int,struct usb_hub*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  usb_set_lpm_sel (struct usb_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_set_lpm_parameters(struct usb_device *udev)
{
	struct usb_hub *hub;
	unsigned int port_to_port_delay;
	unsigned int udev_u1_del;
	unsigned int udev_u2_del;
	unsigned int hub_u1_del;
	unsigned int hub_u2_del;

	if (!udev->lpm_capable || udev->speed != USB_SPEED_SUPER)
		return;

	hub = hdev_to_hub(udev->parent);
	/* It doesn't take time to transition the roothub into U0, since it
	 * doesn't have an upstream link.
	 */
	if (!hub)
		return;

	udev_u1_del = udev->bos->ss_cap->bU1devExitLat;
	udev_u2_del = udev->bos->ss_cap->bU2DevExitLat;
	hub_u1_del = udev->parent->bos->ss_cap->bU1devExitLat;
	hub_u2_del = udev->parent->bos->ss_cap->bU2DevExitLat;

	usb_set_lpm_mel(udev, &udev->u1_params, udev_u1_del,
			hub, &udev->parent->u1_params, hub_u1_del);

	usb_set_lpm_mel(udev, &udev->u2_params, udev_u2_del,
			hub, &udev->parent->u2_params, hub_u2_del);

	/*
	 * Appendix C, section C.2.2.2, says that there is a slight delay from
	 * when the parent hub notices the downstream port is trying to
	 * transition to U0 to when the hub initiates a U0 transition on its
	 * upstream port.  The section says the delays are tPort2PortU1EL and
	 * tPort2PortU2EL, but it doesn't define what they are.
	 *
	 * The hub chapter, sections 10.4.2.4 and 10.4.2.5 seem to be talking
	 * about the same delays.  Use the maximum delay calculations from those
	 * sections.  For U1, it's tHubPort2PortExitLat, which is 1us max.  For
	 * U2, it's tHubPort2PortExitLat + U2DevExitLat - U1DevExitLat.  I
	 * assume the device exit latencies they are talking about are the hub
	 * exit latencies.
	 *
	 * What do we do if the U2 exit latency is less than the U1 exit
	 * latency?  It's possible, although not likely...
	 */
	port_to_port_delay = 1;

	usb_set_lpm_pel(udev, &udev->u1_params, udev_u1_del,
			hub, &udev->parent->u1_params, hub_u1_del,
			port_to_port_delay);

	if (hub_u2_del > hub_u1_del)
		port_to_port_delay = 1 + hub_u2_del - hub_u1_del;
	else
		port_to_port_delay = 1 + hub_u1_del;

	usb_set_lpm_pel(udev, &udev->u2_params, udev_u2_del,
			hub, &udev->parent->u2_params, hub_u2_del,
			port_to_port_delay);

	/* Now that we've got PEL, calculate SEL. */
	usb_set_lpm_sel(udev, &udev->u1_params);
	usb_set_lpm_sel(udev, &udev->u2_params);
}