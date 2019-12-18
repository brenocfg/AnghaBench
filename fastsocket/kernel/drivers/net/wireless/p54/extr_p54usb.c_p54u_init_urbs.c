#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct urb {int dummy; } ;
struct sk_buff {scalar_t__ cb; } ;
struct p54u_rx_info {struct ieee80211_hw* dev; struct urb* urb; } ;
struct TYPE_2__ {scalar_t__ rx_mtu; } ;
struct p54u_priv {int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  submitted; TYPE_1__ common; int /*<<< orphan*/  udev; } ;
struct ieee80211_hw {struct p54u_priv* priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  P54U_PIPE_DATA ; 
 struct sk_buff* __dev_alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  p54u_free_urbs (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  p54u_rx_cb ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_unlink (struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static int p54u_init_urbs(struct ieee80211_hw *dev)
{
	struct p54u_priv *priv = dev->priv;
	struct urb *entry = NULL;
	struct sk_buff *skb;
	struct p54u_rx_info *info;
	int ret = 0;

	while (skb_queue_len(&priv->rx_queue) < 32) {
		skb = __dev_alloc_skb(priv->common.rx_mtu + 32, GFP_KERNEL);
		if (!skb) {
			ret = -ENOMEM;
			goto err;
		}
		entry = usb_alloc_urb(0, GFP_KERNEL);
		if (!entry) {
			ret = -ENOMEM;
			goto err;
		}

		usb_fill_bulk_urb(entry, priv->udev,
				  usb_rcvbulkpipe(priv->udev, P54U_PIPE_DATA),
				  skb_tail_pointer(skb),
				  priv->common.rx_mtu + 32, p54u_rx_cb, skb);
		info = (struct p54u_rx_info *) skb->cb;
		info->urb = entry;
		info->dev = dev;
		skb_queue_tail(&priv->rx_queue, skb);

		usb_anchor_urb(entry, &priv->submitted);
		ret = usb_submit_urb(entry, GFP_KERNEL);
		if (ret) {
			skb_unlink(skb, &priv->rx_queue);
			usb_unanchor_urb(entry);
			goto err;
		}
		usb_free_urb(entry);
		entry = NULL;
	}

	return 0;

 err:
	usb_free_urb(entry);
	kfree_skb(skb);
	p54u_free_urbs(dev);
	return ret;
}