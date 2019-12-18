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
struct usb_request {struct page* context; int /*<<< orphan*/  length; int /*<<< orphan*/  buf; } ;
struct page {int dummy; } ;
struct net_device {int dummy; } ;
struct f_phonet {int /*<<< orphan*/  out_ep; struct net_device* dev; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct page* __netdev_alloc_page (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_free_page (struct net_device*,struct page*) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int usb_ep_queue (int /*<<< orphan*/ ,struct usb_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pn_rx_submit(struct f_phonet *fp, struct usb_request *req, gfp_t gfp_flags)
{
	struct net_device *dev = fp->dev;
	struct page *page;
	int err;

	page = __netdev_alloc_page(dev, gfp_flags);
	if (!page)
		return -ENOMEM;

	req->buf = page_address(page);
	req->length = PAGE_SIZE;
	req->context = page;

	err = usb_ep_queue(fp->out_ep, req, gfp_flags);
	if (unlikely(err))
		netdev_free_page(dev, page);
	return err;
}