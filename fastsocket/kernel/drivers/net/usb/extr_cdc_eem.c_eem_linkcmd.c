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
struct usbnet {int /*<<< orphan*/  out; int /*<<< orphan*/  udev; } ;
struct urb {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  devwarn (struct usbnet*,char*) ; 
 int /*<<< orphan*/  eem_linkcmd_complete ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eem_linkcmd(struct usbnet *dev, struct sk_buff *skb)
{
	struct urb		*urb;
	int			status;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!urb)
		goto fail;

	usb_fill_bulk_urb(urb, dev->udev, dev->out,
			skb->data, skb->len, eem_linkcmd_complete, skb);

	status = usb_submit_urb(urb, GFP_ATOMIC);
	if (status) {
		usb_free_urb(urb);
fail:
		dev_kfree_skb(skb);
		devwarn(dev, "link cmd failure\n");
		return;
	}
}