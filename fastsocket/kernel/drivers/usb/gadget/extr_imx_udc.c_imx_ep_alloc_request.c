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
struct usb_request {int dummy; } ;
struct usb_ep {int dummy; } ;
struct imx_request {struct usb_request req; scalar_t__ in_use; int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct imx_request* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct usb_request *imx_ep_alloc_request
					(struct usb_ep *usb_ep, gfp_t gfp_flags)
{
	struct imx_request *req;

	if (!usb_ep)
		return NULL;

	req = kzalloc(sizeof *req, gfp_flags);
	if (!req)
		return NULL;

	INIT_LIST_HEAD(&req->queue);
	req->in_use = 0;

	return &req->req;
}