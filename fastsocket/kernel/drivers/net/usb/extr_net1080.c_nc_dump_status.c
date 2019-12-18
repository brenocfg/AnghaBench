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
typedef  int u16 ;
struct usbnet {TYPE_2__* udev; } ;
struct TYPE_4__ {int /*<<< orphan*/  devpath; TYPE_1__* bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus_name; } ;

/* Variables and functions */
 int STATUS_CONN_OTHER ; 
 int STATUS_CONN_THIS ; 
 int STATUS_MAILBOX_OTHER ; 
 int STATUS_MAILBOX_THIS ; 
 int /*<<< orphan*/  STATUS_PACKETS_OTHER (int) ; 
 int /*<<< orphan*/  STATUS_PACKETS_THIS (int) ; 
 int STATUS_PORT_A ; 
 int STATUS_SUSPEND_OTHER ; 
 int STATUS_SUSPEND_THIS ; 
 int STATUS_UNSPEC_MASK ; 
 int /*<<< orphan*/  devdbg (struct usbnet*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char,int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ ,char*,char*,char*,int) ; 
 int /*<<< orphan*/  netif_msg_link (struct usbnet*) ; 

__attribute__((used)) static inline void nc_dump_status(struct usbnet *dev, u16 status)
{
	if (!netif_msg_link(dev))
		return;
	devdbg(dev, "net1080 %s-%s status 0x%x:"
			" this (%c) PKT=%d%s%s%s;"
			" other PKT=%d%s%s%s; unspec 0x%x",
		dev->udev->bus->bus_name, dev->udev->devpath,
		status,

		// XXX the packet counts don't seem right
		// (1 at reset, not 0); maybe UNSPEC too

		(status & STATUS_PORT_A) ? 'A' : 'B',
		STATUS_PACKETS_THIS(status),
		(status & STATUS_CONN_THIS) ? " CON" : "",
		(status & STATUS_SUSPEND_THIS) ? " SUS" : "",
		(status & STATUS_MAILBOX_THIS) ? " MBOX" : "",

		STATUS_PACKETS_OTHER(status),
		(status & STATUS_CONN_OTHER) ? " CON" : "",
		(status & STATUS_SUSPEND_OTHER) ? " SUS" : "",
		(status & STATUS_MAILBOX_OTHER) ? " MBOX" : "",

		status & STATUS_UNSPEC_MASK
		);
}