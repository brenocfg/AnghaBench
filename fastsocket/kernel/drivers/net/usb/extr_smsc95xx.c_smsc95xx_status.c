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
typedef  int u32 ;
struct usbnet {int dummy; } ;
struct urb {int actual_length; int /*<<< orphan*/  transfer_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_LINK_RESET ; 
 int INT_ENP_PHY_INT_ ; 
 int /*<<< orphan*/  devdbg (struct usbnet*,char*,int) ; 
 int /*<<< orphan*/  devwarn (struct usbnet*,char*,int) ; 
 int /*<<< orphan*/  le32_to_cpus (int*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ netif_msg_link (struct usbnet*) ; 
 int /*<<< orphan*/  usbnet_defer_kevent (struct usbnet*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smsc95xx_status(struct usbnet *dev, struct urb *urb)
{
	u32 intdata;

	if (urb->actual_length != 4) {
		devwarn(dev, "unexpected urb length %d", urb->actual_length);
		return;
	}

	memcpy(&intdata, urb->transfer_buffer, 4);
	le32_to_cpus(&intdata);

	if (netif_msg_link(dev))
		devdbg(dev, "intdata: 0x%08X", intdata);

	if (intdata & INT_ENP_PHY_INT_)
		usbnet_defer_kevent(dev, EVENT_LINK_RESET);
	else
		devwarn(dev, "unexpected interrupt, intdata=0x%08X", intdata);
}