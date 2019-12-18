#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_endpoint_descriptor {int /*<<< orphan*/  bEndpointAddress; } ;
struct sk_buff {int /*<<< orphan*/  data; int /*<<< orphan*/  ip_summed; struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct i1480u_rx_buf {int /*<<< orphan*/ * urb; struct sk_buff* data; struct i1480u* i1480u; } ;
struct i1480u {int /*<<< orphan*/  usb_dev; struct i1480u_rx_buf* rx_buf; TYPE_3__* usb_iface; int /*<<< orphan*/ * rx_skb; struct net_device* net_dev; } ;
struct device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* cur_altsetting; struct device dev; } ;
struct TYPE_5__ {TYPE_1__* endpoint; } ;
struct TYPE_4__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 scalar_t__ i1480u_MAX_RX_PKT_SIZE ; 
 int i1480u_RX_BUFS ; 
 int /*<<< orphan*/  i1480u_rx_cb ; 
 int /*<<< orphan*/  i1480u_rx_release (struct i1480u*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct i1480u_rx_buf*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int i1480u_rx_setup(struct i1480u *i1480u)
{
	int result, cnt;
	struct device *dev = &i1480u->usb_iface->dev;
	struct net_device *net_dev = i1480u->net_dev;
	struct usb_endpoint_descriptor *epd;
	struct sk_buff *skb;

	/* Alloc RX stuff */
	i1480u->rx_skb = NULL;	/* not in process of receiving packet */
	result = -ENOMEM;
	epd = &i1480u->usb_iface->cur_altsetting->endpoint[1].desc;
	for (cnt = 0; cnt < i1480u_RX_BUFS; cnt++) {
		struct i1480u_rx_buf *rx_buf = &i1480u->rx_buf[cnt];
		rx_buf->i1480u = i1480u;
		skb = dev_alloc_skb(i1480u_MAX_RX_PKT_SIZE);
		if (!skb) {
			dev_err(dev,
				"RX: cannot allocate RX buffer %d\n", cnt);
			result = -ENOMEM;
			goto error;
		}
		skb->dev = net_dev;
		skb->ip_summed = CHECKSUM_NONE;
		skb_reserve(skb, 2);
		rx_buf->data = skb;
		rx_buf->urb = usb_alloc_urb(0, GFP_KERNEL);
		if (unlikely(rx_buf->urb == NULL)) {
			dev_err(dev, "RX: cannot allocate URB %d\n", cnt);
			result = -ENOMEM;
			goto error;
		}
		usb_fill_bulk_urb(rx_buf->urb, i1480u->usb_dev,
			  usb_rcvbulkpipe(i1480u->usb_dev, epd->bEndpointAddress),
			  rx_buf->data->data, i1480u_MAX_RX_PKT_SIZE - 2,
			  i1480u_rx_cb, rx_buf);
		result = usb_submit_urb(rx_buf->urb, GFP_NOIO);
		if (unlikely(result < 0)) {
			dev_err(dev, "RX: cannot submit URB %d: %d\n",
				cnt, result);
			goto error;
		}
	}
	return 0;

error:
	i1480u_rx_release(i1480u);
	return result;
}