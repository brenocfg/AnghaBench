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
struct usb_request {scalar_t__ actual; scalar_t__ status; struct kiocb_priv* buf; struct kiocb* context; } ;
struct usb_ep {int /*<<< orphan*/  name; } ;
struct kiocb_priv {scalar_t__ actual; struct kiocb_priv* buf; int /*<<< orphan*/ * iv; struct ep_data* epdata; int /*<<< orphan*/ * req; } ;
struct kiocb {struct kiocb_priv* private; } ;
struct ep_data {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (TYPE_1__*,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  aio_complete (struct kiocb*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct kiocb_priv*) ; 
 int /*<<< orphan*/  kick_iocb (struct kiocb*) ; 
 int /*<<< orphan*/  put_ep (struct ep_data*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_ep_free_request (struct usb_ep*,struct usb_request*) ; 

__attribute__((used)) static void ep_aio_complete(struct usb_ep *ep, struct usb_request *req)
{
	struct kiocb		*iocb = req->context;
	struct kiocb_priv	*priv = iocb->private;
	struct ep_data		*epdata = priv->epdata;

	/* lock against disconnect (and ideally, cancel) */
	spin_lock(&epdata->dev->lock);
	priv->req = NULL;
	priv->epdata = NULL;

	/* if this was a write or a read returning no data then we
	 * don't need to copy anything to userspace, so we can
	 * complete the aio request immediately.
	 */
	if (priv->iv == NULL || unlikely(req->actual == 0)) {
		kfree(req->buf);
		kfree(priv);
		iocb->private = NULL;
		/* aio_complete() reports bytes-transferred _and_ faults */
		aio_complete(iocb, req->actual ? req->actual : req->status,
				req->status);
	} else {
		/* retry() won't report both; so we hide some faults */
		if (unlikely(0 != req->status))
			DBG(epdata->dev, "%s fault %d len %d\n",
				ep->name, req->status, req->actual);

		priv->buf = req->buf;
		priv->actual = req->actual;
		kick_iocb(iocb);
	}
	spin_unlock(&epdata->dev->lock);

	usb_ep_free_request(ep, req);
	put_ep(epdata);
}