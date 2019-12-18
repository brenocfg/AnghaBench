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
struct usbpn_dev {int /*<<< orphan*/  rx_pipe; int /*<<< orphan*/  usb; struct net_device* dev; } ;
struct urb {scalar_t__ transfer_flags; } ;
struct page {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct page* __netdev_alloc_page (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  netdev_free_page (struct net_device*,struct page*) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  rx_complete ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rx_submit(struct usbpn_dev *pnd, struct urb *req, gfp_t gfp_flags)
{
	struct net_device *dev = pnd->dev;
	struct page *page;
	int err;

	page = __netdev_alloc_page(dev, gfp_flags);
	if (!page)
		return -ENOMEM;

	usb_fill_bulk_urb(req, pnd->usb, pnd->rx_pipe, page_address(page),
				PAGE_SIZE, rx_complete, dev);
	req->transfer_flags = 0;
	err = usb_submit_urb(req, gfp_flags);
	if (unlikely(err)) {
		dev_dbg(&dev->dev, "RX submit error (%d)\n", err);
		netdev_free_page(dev, page);
	}
	return err;
}