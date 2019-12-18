#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wlp_tx_hdr {int dummy; } ;
struct wlp {int /*<<< orphan*/  start_queue; int /*<<< orphan*/  stop_queue; int /*<<< orphan*/  fill_device_info; int /*<<< orphan*/  xmit_frame; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct uwb_dev {TYPE_1__ mac_addr; } ;
struct uwb_rc {struct uwb_dev uwb_dev; } ;
struct usb_interface {TYPE_3__* cur_altsetting; int /*<<< orphan*/  dev; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_device {int dummy; } ;
struct untd_hdr_cmp {int dummy; } ;
struct net_device {int mtu; int tx_queue_len; int watchdog_timeo; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  features; int /*<<< orphan*/  flags; scalar_t__ hard_header_len; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  restart_ts; int /*<<< orphan*/  threshold; int /*<<< orphan*/  max; } ;
struct i1480u {TYPE_5__* usb_dev; TYPE_4__ tx_inflight; int /*<<< orphan*/  notif_buffer; int /*<<< orphan*/ * notif_urb; struct usb_interface* usb_iface; struct net_device* net_dev; struct wlp wlp; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {TYPE_2__* endpoint; } ;
struct TYPE_8__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  IFF_MULTICAST ; 
 int /*<<< orphan*/  NETIF_F_FRAGLIST ; 
 int /*<<< orphan*/  NETIF_F_HIGHDMA ; 
 int /*<<< orphan*/  NETIF_F_SG ; 
 scalar_t__ WLP_DATA_HLEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  i1480u_TX_INFLIGHT_MAX ; 
 int /*<<< orphan*/  i1480u_TX_INFLIGHT_THRESHOLD ; 
 int /*<<< orphan*/  i1480u_fill_device_info ; 
 int /*<<< orphan*/  i1480u_netdev_ops ; 
 int /*<<< orphan*/  i1480u_notif_cb ; 
 int /*<<< orphan*/  i1480u_start_queue ; 
 int /*<<< orphan*/  i1480u_stop_queue ; 
 int /*<<< orphan*/  i1480u_xmit_frame ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ *,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct i1480u*,int /*<<< orphan*/ ) ; 
 TYPE_5__* usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_put_dev (TYPE_5__*) ; 
 int /*<<< orphan*/  usb_rcvintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct i1480u*) ; 
 struct uwb_rc* uwb_rc_get_by_grandpa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_rc_put (struct uwb_rc*) ; 
 int /*<<< orphan*/  wlp_remove (struct wlp*) ; 
 int wlp_setup (struct wlp*,struct uwb_rc*,struct net_device*) ; 

__attribute__((used)) static
int i1480u_add(struct i1480u *i1480u, struct usb_interface *iface)
{
	int result = -ENODEV;
	struct wlp *wlp = &i1480u->wlp;
	struct usb_device *usb_dev = interface_to_usbdev(iface);
	struct net_device *net_dev = i1480u->net_dev;
	struct uwb_rc *rc;
	struct uwb_dev *uwb_dev;
#ifdef i1480u_FLOW_CONTROL
	struct usb_endpoint_descriptor *epd;
#endif

	i1480u->usb_dev = usb_get_dev(usb_dev);
	i1480u->usb_iface = iface;
	rc = uwb_rc_get_by_grandpa(&i1480u->usb_dev->dev);
	if (rc == NULL) {
		dev_err(&iface->dev, "Cannot get associated UWB Radio "
			"Controller\n");
		goto out;
	}
	wlp->xmit_frame = i1480u_xmit_frame;
	wlp->fill_device_info = i1480u_fill_device_info;
	wlp->stop_queue = i1480u_stop_queue;
	wlp->start_queue = i1480u_start_queue;
	result = wlp_setup(wlp, rc, net_dev);
	if (result < 0) {
		dev_err(&iface->dev, "Cannot setup WLP\n");
		goto error_wlp_setup;
	}
	result = 0;
	ether_setup(net_dev);			/* make it an etherdevice */
	uwb_dev = &rc->uwb_dev;
	/* FIXME: hookup address change notifications? */

	memcpy(net_dev->dev_addr, uwb_dev->mac_addr.data,
	       sizeof(net_dev->dev_addr));

	net_dev->hard_header_len = sizeof(struct untd_hdr_cmp)
		+ sizeof(struct wlp_tx_hdr)
		+ WLP_DATA_HLEN
		+ ETH_HLEN;
	net_dev->mtu = 3500;
	net_dev->tx_queue_len = 20;		/* FIXME: maybe use 1000? */

/*	net_dev->flags &= ~IFF_BROADCAST;	FIXME: BUG in firmware */
	/* FIXME: multicast disabled */
	net_dev->flags &= ~IFF_MULTICAST;
	net_dev->features &= ~NETIF_F_SG;
	net_dev->features &= ~NETIF_F_FRAGLIST;
	/* All NETIF_F_*_CSUM disabled */
	net_dev->features |= NETIF_F_HIGHDMA;
	net_dev->watchdog_timeo = 5*HZ;		/* FIXME: a better default? */

	net_dev->netdev_ops = &i1480u_netdev_ops;

#ifdef i1480u_FLOW_CONTROL
	/* Notification endpoint setup (submitted when we open the device) */
	i1480u->notif_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (i1480u->notif_urb == NULL) {
		dev_err(&iface->dev, "Unable to allocate notification URB\n");
		result = -ENOMEM;
		goto error_urb_alloc;
	}
	epd = &iface->cur_altsetting->endpoint[0].desc;
	usb_fill_int_urb(i1480u->notif_urb, usb_dev,
			 usb_rcvintpipe(usb_dev, epd->bEndpointAddress),
			 i1480u->notif_buffer, sizeof(i1480u->notif_buffer),
			 i1480u_notif_cb, i1480u, epd->bInterval);

#endif

	i1480u->tx_inflight.max = i1480u_TX_INFLIGHT_MAX;
	i1480u->tx_inflight.threshold = i1480u_TX_INFLIGHT_THRESHOLD;
	i1480u->tx_inflight.restart_ts = jiffies;
	usb_set_intfdata(iface, i1480u);
	return result;

#ifdef i1480u_FLOW_CONTROL
error_urb_alloc:
#endif
	wlp_remove(wlp);
error_wlp_setup:
	uwb_rc_put(rc);
out:
	usb_put_dev(i1480u->usb_dev);
	return result;
}