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
struct wusbhc {int /*<<< orphan*/  mutex; } ;
struct wusb_dev {int dummy; } ;
struct wahc {struct wusbhc* wusb; } ;
struct wa_xfer {int result; int /*<<< orphan*/  lock; TYPE_1__* ep; struct wusb_dev* wusb_dev; int /*<<< orphan*/  gfp; struct wahc* wa; struct urb* urb; } ;
struct urb {int status; int /*<<< orphan*/ * dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  hcpriv; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int ENODEV ; 
 unsigned int __wa_xfer_is_done (struct wa_xfer*) ; 
 int __wa_xfer_setup (struct wa_xfer*,struct urb*) ; 
 int __wa_xfer_submit (struct wa_xfer*) ; 
 struct wusb_dev* __wusb_dev_get_by_usb_dev (struct wusbhc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rpipe_get_by_ep (struct wahc*,TYPE_1__*,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpipe_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wa_xfer_completion (struct wa_xfer*) ; 
 int /*<<< orphan*/  wa_xfer_giveback (struct wa_xfer*) ; 
 int /*<<< orphan*/  wusb_dev_put (struct wusb_dev*) ; 

__attribute__((used)) static void wa_urb_enqueue_b(struct wa_xfer *xfer)
{
	int result;
	unsigned long flags;
	struct urb *urb = xfer->urb;
	struct wahc *wa = xfer->wa;
	struct wusbhc *wusbhc = wa->wusb;
	struct wusb_dev *wusb_dev;
	unsigned done;

	result = rpipe_get_by_ep(wa, xfer->ep, urb, xfer->gfp);
	if (result < 0)
		goto error_rpipe_get;
	result = -ENODEV;
	/* FIXME: segmentation broken -- kills DWA */
	mutex_lock(&wusbhc->mutex);		/* get a WUSB dev */
	if (urb->dev == NULL) {
		mutex_unlock(&wusbhc->mutex);
		goto error_dev_gone;
	}
	wusb_dev = __wusb_dev_get_by_usb_dev(wusbhc, urb->dev);
	if (wusb_dev == NULL) {
		mutex_unlock(&wusbhc->mutex);
		goto error_dev_gone;
	}
	mutex_unlock(&wusbhc->mutex);

	spin_lock_irqsave(&xfer->lock, flags);
	xfer->wusb_dev = wusb_dev;
	result = urb->status;
	if (urb->status != -EINPROGRESS)
		goto error_dequeued;

	result = __wa_xfer_setup(xfer, urb);
	if (result < 0)
		goto error_xfer_setup;
	result = __wa_xfer_submit(xfer);
	if (result < 0)
		goto error_xfer_submit;
	spin_unlock_irqrestore(&xfer->lock, flags);
	return;

	/* this is basically wa_xfer_completion() broken up wa_xfer_giveback()
	 * does a wa_xfer_put() that will call wa_xfer_destroy() and clean
	 * upundo setup().
	 */
error_xfer_setup:
error_dequeued:
	spin_unlock_irqrestore(&xfer->lock, flags);
	/* FIXME: segmentation broken, kills DWA */
	if (wusb_dev)
		wusb_dev_put(wusb_dev);
error_dev_gone:
	rpipe_put(xfer->ep->hcpriv);
error_rpipe_get:
	xfer->result = result;
	wa_xfer_giveback(xfer);
	return;

error_xfer_submit:
	done = __wa_xfer_is_done(xfer);
	xfer->result = result;
	spin_unlock_irqrestore(&xfer->lock, flags);
	if (done)
		wa_xfer_completion(xfer);
}