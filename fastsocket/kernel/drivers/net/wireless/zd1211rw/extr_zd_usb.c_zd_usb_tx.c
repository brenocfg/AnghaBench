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
struct zd_usb_tx {int /*<<< orphan*/  submitted_skbs; int /*<<< orphan*/  submitted; int /*<<< orphan*/  enabled; } ;
struct zd_usb {struct zd_usb_tx tx; } ;
struct usb_device {int dummy; } ;
struct urb {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct ieee80211_tx_info {void** rate_driver_data; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EP_DATA_OUT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,struct urb*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_unlink (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_inc_submitted_urbs (struct zd_usb*) ; 
 int /*<<< orphan*/  tx_urb_complete ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 
 int /*<<< orphan*/  zd_usb_dev (struct zd_usb*) ; 
 struct usb_device* zd_usb_to_usbdev (struct zd_usb*) ; 

int zd_usb_tx(struct zd_usb *usb, struct sk_buff *skb)
{
	int r;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct usb_device *udev = zd_usb_to_usbdev(usb);
	struct urb *urb;
	struct zd_usb_tx *tx = &usb->tx;

	if (!atomic_read(&tx->enabled)) {
		r = -ENOENT;
		goto out;
	}

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!urb) {
		r = -ENOMEM;
		goto out;
	}

	usb_fill_bulk_urb(urb, udev, usb_sndbulkpipe(udev, EP_DATA_OUT),
		          skb->data, skb->len, tx_urb_complete, skb);

	info->rate_driver_data[1] = (void *)jiffies;
	skb_queue_tail(&tx->submitted_skbs, skb);
	usb_anchor_urb(urb, &tx->submitted);

	r = usb_submit_urb(urb, GFP_ATOMIC);
	if (r) {
		dev_dbg_f(zd_usb_dev(usb), "error submit urb %p %d\n", urb, r);
		usb_unanchor_urb(urb);
		skb_unlink(skb, &tx->submitted_skbs);
		goto error;
	}
	tx_inc_submitted_urbs(usb);
	return 0;
error:
	usb_free_urb(urb);
out:
	return r;
}