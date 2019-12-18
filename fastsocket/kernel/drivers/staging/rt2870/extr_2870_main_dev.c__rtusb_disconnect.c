#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_device {int /*<<< orphan*/  devpath; TYPE_1__* bus; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {struct net_device* net_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  bus_name; } ;
typedef  TYPE_2__* PRTMP_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPRINT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RTMPFreeAdapter (TYPE_2__*) ; 
 int /*<<< orphan*/  RTMP_SET_FLAG (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_DEBUG_ERROR ; 
 int /*<<< orphan*/  fRTMP_ADAPTER_NIC_NOT_EXIST ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 

__attribute__((used)) static void _rtusb_disconnect(struct usb_device *dev, PRTMP_ADAPTER pAd)
{
	struct net_device	*net_dev = NULL;


	DBGPRINT(RT_DEBUG_ERROR, ("rtusb_disconnect: unregister usbnet usb-%s-%s\n",
				dev->bus->bus_name, dev->devpath));
	if (!pAd)
	{
		usb_put_dev(dev);

		printk("rtusb_disconnect: pAd == NULL!\n");
		return;
	}
	RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST);



	// for debug, wait to show some messages to /proc system
	udelay(1);




	net_dev = pAd->net_dev;
	if (pAd->net_dev != NULL)
	{
		printk("rtusb_disconnect: unregister_netdev(), dev->name=%s!\n", net_dev->name);
		unregister_netdev (pAd->net_dev);
	}
	udelay(1);
	flush_scheduled_work();
	udelay(1);

	// free net_device memory
	free_netdev(net_dev);

	// free adapter memory
	RTMPFreeAdapter(pAd);

	// release a use of the usb device structure
	usb_put_dev(dev);
	udelay(1);

	DBGPRINT(RT_DEBUG_ERROR, (" RTUSB disconnect successfully\n"));
}