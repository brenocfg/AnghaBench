#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int bLength; } ;
struct wuie_keep_alive {int* bDeviceAddress; TYPE_2__ hdr; } ;
struct wusbhc {unsigned int ports_max; int /*<<< orphan*/  trust_timeout; struct wuie_keep_alive keep_alive_ie; struct device* dev; } ;
struct wusb_port {struct wusb_dev* wusb_dev; } ;
struct wusb_dev {int addr; scalar_t__ entry_ts; TYPE_1__* usb_dev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  authenticated; } ;

/* Variables and functions */
 unsigned int WUIE_ELT_MAX ; 
 int /*<<< orphan*/  __wusbhc_dev_disconnect (struct wusbhc*,struct wusb_port*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  jiffies ; 
 unsigned int msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 struct wusb_port* wusb_port_by_idx (struct wusbhc*,unsigned int) ; 
 int /*<<< orphan*/  wusbhc_mmcie_rm (struct wusbhc*,TYPE_2__*) ; 
 int /*<<< orphan*/  wusbhc_mmcie_set (struct wusbhc*,int,int,TYPE_2__*) ; 

__attribute__((used)) static void __wusbhc_keep_alive(struct wusbhc *wusbhc)
{
	struct device *dev = wusbhc->dev;
	unsigned cnt;
	struct wusb_dev *wusb_dev;
	struct wusb_port *wusb_port;
	struct wuie_keep_alive *ie = &wusbhc->keep_alive_ie;
	unsigned keep_alives, old_keep_alives;

	old_keep_alives = ie->hdr.bLength - sizeof(ie->hdr);
	keep_alives = 0;
	for (cnt = 0;
	     keep_alives <= WUIE_ELT_MAX && cnt < wusbhc->ports_max;
	     cnt++) {
		unsigned tt = msecs_to_jiffies(wusbhc->trust_timeout);

		wusb_port = wusb_port_by_idx(wusbhc, cnt);
		wusb_dev = wusb_port->wusb_dev;

		if (wusb_dev == NULL)
			continue;
		if (wusb_dev->usb_dev == NULL || !wusb_dev->usb_dev->authenticated)
			continue;

		if (time_after(jiffies, wusb_dev->entry_ts + tt)) {
			dev_err(dev, "KEEPALIVE: device %u timed out\n",
				wusb_dev->addr);
			__wusbhc_dev_disconnect(wusbhc, wusb_port);
		} else if (time_after(jiffies, wusb_dev->entry_ts + tt/2)) {
			/* Approaching timeout cut out, need to refresh */
			ie->bDeviceAddress[keep_alives++] = wusb_dev->addr;
		}
	}
	if (keep_alives & 0x1)	/* pad to even number ([WUSB] section 7.5.9) */
		ie->bDeviceAddress[keep_alives++] = 0x7f;
	ie->hdr.bLength = sizeof(ie->hdr) +
		keep_alives*sizeof(ie->bDeviceAddress[0]);
	if (keep_alives > 0)
		wusbhc_mmcie_set(wusbhc, 10, 5, &ie->hdr);
	else if (old_keep_alives != 0)
		wusbhc_mmcie_rm(wusbhc, &ie->hdr);
}