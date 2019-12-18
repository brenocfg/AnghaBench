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
struct zd1201 {int endp_in; int endp_out; int endp_out2; void* rx_urb; void* tx_urb; scalar_t__ ap; int /*<<< orphan*/  fraglist; int /*<<< orphan*/  rxdataq; scalar_t__ removed; struct usb_device* usb; struct net_device* dev; } ;
struct usb_interface {int dummy; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * wireless_handlers; int /*<<< orphan*/ * netdev_ops; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int IW_ESSID_MAX_SIZE ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZD1201_CMDCODE_INIT ; 
 short ZD1201_PORTTYPE_AP ; 
 short ZD1201_PORTTYPE_BSS ; 
 short ZD1201_RATEB1 ; 
 short ZD1201_RATEB11 ; 
 short ZD1201_RATEB2 ; 
 short ZD1201_RATEB5 ; 
 int /*<<< orphan*/  ZD1201_RID_CNFDESIREDSSID ; 
 int /*<<< orphan*/  ZD1201_RID_CNFMAXDATALEN ; 
 int /*<<< orphan*/  ZD1201_RID_CNFOWNMACADDR ; 
 int /*<<< orphan*/  ZD1201_RID_CNFPORTTYPE ; 
 int /*<<< orphan*/  ZD1201_RID_TXRATECNTL ; 
 int /*<<< orphan*/  ZD1201_TX_TIMEOUT ; 
 struct net_device* alloc_etherdev (int) ; 
 scalar_t__ ap ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct zd1201* netdev_priv (struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (void*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct zd1201*) ; 
 int /*<<< orphan*/  zd1201_disable (struct zd1201*) ; 
 int /*<<< orphan*/  zd1201_docmd (struct zd1201*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zd1201_drvr_start (struct zd1201*) ; 
 int /*<<< orphan*/  zd1201_enable (struct zd1201*) ; 
 int zd1201_fw_upload (struct usb_device*,scalar_t__) ; 
 int zd1201_getconfig (struct zd1201*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zd1201_iw_handlers ; 
 int /*<<< orphan*/  zd1201_netdev_ops ; 
 int zd1201_setconfig (struct zd1201*,int /*<<< orphan*/ ,char*,int,int) ; 
 int zd1201_setconfig16 (struct zd1201*,int /*<<< orphan*/ ,short) ; 

__attribute__((used)) static int zd1201_probe(struct usb_interface *interface,
			const struct usb_device_id *id)
{
	struct zd1201 *zd;
	struct net_device *dev;
	struct usb_device *usb;
	int err;
	short porttype;
	char buf[IW_ESSID_MAX_SIZE+2];

	usb = interface_to_usbdev(interface);

	dev = alloc_etherdev(sizeof(*zd));
	if (!dev)
		return -ENOMEM;
	zd = netdev_priv(dev);
	zd->dev = dev;

	zd->ap = ap;
	zd->usb = usb;
	zd->removed = 0;
	init_waitqueue_head(&zd->rxdataq);
	INIT_HLIST_HEAD(&zd->fraglist);
	
	err = zd1201_fw_upload(usb, zd->ap);
	if (err) {
		dev_err(&usb->dev, "zd1201 firmware upload failed: %d\n", err);
		goto err_zd;
	}
	
	zd->endp_in = 1;
	zd->endp_out = 1;
	zd->endp_out2 = 2;
	zd->rx_urb = usb_alloc_urb(0, GFP_KERNEL);
	zd->tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!zd->rx_urb || !zd->tx_urb)
		goto err_zd;

	mdelay(100);
	err = zd1201_drvr_start(zd);
	if (err)
		goto err_zd;

	err = zd1201_setconfig16(zd, ZD1201_RID_CNFMAXDATALEN, 2312);
	if (err)
		goto err_start;

	err = zd1201_setconfig16(zd, ZD1201_RID_TXRATECNTL,
	    ZD1201_RATEB1 | ZD1201_RATEB2 | ZD1201_RATEB5 | ZD1201_RATEB11);
	if (err)
		goto err_start;

	dev->netdev_ops = &zd1201_netdev_ops;
	dev->wireless_handlers = &zd1201_iw_handlers;
	dev->watchdog_timeo = ZD1201_TX_TIMEOUT;
	strcpy(dev->name, "wlan%d");

	err = zd1201_getconfig(zd, ZD1201_RID_CNFOWNMACADDR, 
	    dev->dev_addr, dev->addr_len);
	if (err)
		goto err_start;

	/* Set wildcard essid to match zd->essid */
	*(__le16 *)buf = cpu_to_le16(0);
	err = zd1201_setconfig(zd, ZD1201_RID_CNFDESIREDSSID, buf,
	    IW_ESSID_MAX_SIZE+2, 1);
	if (err)
		goto err_start;

	if (zd->ap)
		porttype = ZD1201_PORTTYPE_AP;
	else
		porttype = ZD1201_PORTTYPE_BSS;
	err = zd1201_setconfig16(zd, ZD1201_RID_CNFPORTTYPE, porttype);
	if (err)
		goto err_start;

	SET_NETDEV_DEV(dev, &usb->dev);

	err = register_netdev(dev);
	if (err)
		goto err_start;
	dev_info(&usb->dev, "%s: ZD1201 USB Wireless interface\n",
	    dev->name);

	usb_set_intfdata(interface, zd);
	zd1201_enable(zd);	/* zd1201 likes to startup enabled, */
	zd1201_disable(zd);	/* interfering with all the wifis in range */
	return 0;

err_start:
	/* Leave the device in reset state */
	zd1201_docmd(zd, ZD1201_CMDCODE_INIT, 0, 0, 0);
err_zd:
	usb_free_urb(zd->tx_urb);
	usb_free_urb(zd->rx_urb);
	free_netdev(dev);
	return err;
}