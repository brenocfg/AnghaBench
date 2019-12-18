#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct wusbhc {int ports_max; } ;
struct TYPE_3__ {int /*<<< orphan*/ * DeviceRemovable; } ;
struct TYPE_4__ {TYPE_1__ hs; } ;
struct usb_hub_descriptor {int bDescLength; int bDescriptorType; int bNbrPorts; TYPE_2__ u; scalar_t__ bHubContrCurrent; scalar_t__ bPwrOn2PwrGood; int /*<<< orphan*/  wHubCharacteristics; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int wusbhc_rh_get_hub_descr(struct wusbhc *wusbhc, u16 wValue,
				   u16 wIndex,
				   struct usb_hub_descriptor *descr,
				   u16 wLength)
{
	u16 temp = 1 + (wusbhc->ports_max / 8);
	u8 length = 7 + 2 * temp;

	if (wLength < length)
		return -ENOSPC;
	descr->bDescLength = 7 + 2 * temp;
	descr->bDescriptorType = 0x29;	/* HUB type */
	descr->bNbrPorts = wusbhc->ports_max;
	descr->wHubCharacteristics = cpu_to_le16(
		0x00			/* All ports power at once */
		| 0x00			/* not part of compound device */
		| 0x10			/* No overcurrent protection */
		| 0x00			/* 8 FS think time FIXME ?? */
		| 0x00);		/* No port indicators */
	descr->bPwrOn2PwrGood = 0;
	descr->bHubContrCurrent = 0;
	/* two bitmaps:  ports removable, and usb 1.0 legacy PortPwrCtrlMask */
	memset(&descr->u.hs.DeviceRemovable[0], 0, temp);
	memset(&descr->u.hs.DeviceRemovable[temp], 0xff, temp);
	return 0;
}