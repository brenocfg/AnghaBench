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
typedef  scalar_t__ u32 ;
struct wb_usb {int IsUsb20; struct usb_device* udev; } ;
struct hw_data {struct wb_usb WbUsb; } ;
struct wbsoft_priv {struct hw_data sHwData; int /*<<< orphan*/  SpinLock; } ;
struct usb_interface {struct usb_host_interface* cur_altsetting; } ;
struct usb_host_interface {TYPE_1__* endpoint; } ;
struct usb_endpoint_descriptor {int wMaxPacketSize; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct ieee80211_hw {int extra_tx_headroom; int channel_change_time; int max_signal; int queues; TYPE_2__* wiphy; int /*<<< orphan*/  flags; struct wbsoft_priv* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/ ** bands; int /*<<< orphan*/  interface_modes; } ;
struct TYPE_3__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int ENOMEM ; 
 int HZ ; 
 size_t IEEE80211_BAND_2GHZ ; 
 int /*<<< orphan*/  IEEE80211_HW_SIGNAL_UNSPEC ; 
 int MAX_ADDR_LEN ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  SET_IEEE80211_DEV (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_IEEE80211_PERM_ADDR (struct ieee80211_hw*,unsigned char*) ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 scalar_t__ cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  hal_get_permanent_address (struct hw_data*,unsigned char*) ; 
 struct ieee80211_hw* ieee80211_alloc_hw (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int ieee80211_register_hw (struct ieee80211_hw*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int,int,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct ieee80211_hw*) ; 
 int wb35_hw_init (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  wbsoft_band_2GHz ; 
 int /*<<< orphan*/  wbsoft_ops ; 

__attribute__((used)) static int wb35_probe(struct usb_interface *intf,
		      const struct usb_device_id *id_table)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	struct usb_endpoint_descriptor *endpoint;
	struct usb_host_interface *interface;
	struct ieee80211_hw *dev;
	struct wbsoft_priv *priv;
	struct wb_usb *pWbUsb;
	int nr, err;
	u32 ltmp;

	usb_get_dev(udev);

	/* Check the device if it already be opened */
	nr = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			     0x01,
			     USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_DIR_IN,
			     0x0, 0x400, &ltmp, 4, HZ * 100);
	if (nr < 0) {
		err = nr;
		goto error;
	}

	/* Is already initialized? */
	ltmp = cpu_to_le32(ltmp);
	if (ltmp) {
		err = -EBUSY;
		goto error;
	}

	dev = ieee80211_alloc_hw(sizeof(*priv), &wbsoft_ops);
	if (!dev) {
		err = -ENOMEM;
		goto error;
	}

	priv = dev->priv;

	spin_lock_init(&priv->SpinLock);

	pWbUsb = &priv->sHwData.WbUsb;
	pWbUsb->udev = udev;

	interface = intf->cur_altsetting;
	endpoint = &interface->endpoint[0].desc;

	if (endpoint[2].wMaxPacketSize == 512) {
		printk("[w35und] Working on USB 2.0\n");
		pWbUsb->IsUsb20 = 1;
	}

	err = wb35_hw_init(dev);
	if (err)
		goto error_free_hw;

	SET_IEEE80211_DEV(dev, &udev->dev);
	{
		struct hw_data *pHwData = &priv->sHwData;
		unsigned char dev_addr[MAX_ADDR_LEN];
		hal_get_permanent_address(pHwData, dev_addr);
		SET_IEEE80211_PERM_ADDR(dev, dev_addr);
	}

	dev->extra_tx_headroom = 12;	/* FIXME */
	dev->flags = IEEE80211_HW_SIGNAL_UNSPEC;
	dev->wiphy->interface_modes = BIT(NL80211_IFTYPE_STATION);

	dev->channel_change_time = 1000;
	dev->max_signal = 100;
	dev->queues = 1;

	dev->wiphy->bands[IEEE80211_BAND_2GHZ] = &wbsoft_band_2GHz;

	err = ieee80211_register_hw(dev);
	if (err)
		goto error_free_hw;

	usb_set_intfdata(intf, dev);

	return 0;

error_free_hw:
	ieee80211_free_hw(dev);
error:
	usb_put_dev(udev);
	return err;
}