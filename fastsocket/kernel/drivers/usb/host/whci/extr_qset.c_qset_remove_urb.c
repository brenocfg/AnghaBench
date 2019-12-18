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
struct wusbhc {int /*<<< orphan*/  usb_hcd; } ;
struct whc_urb {int dummy; } ;
struct whc_qset {int dummy; } ;
struct whc {int /*<<< orphan*/  lock; struct wusbhc wusbhc; } ;
struct urb {struct whc_urb* hcpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct whc_urb*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (int /*<<< orphan*/ *,struct urb*) ; 
 int /*<<< orphan*/  wusbhc_giveback_urb (struct wusbhc*,struct urb*,int) ; 

void qset_remove_urb(struct whc *whc, struct whc_qset *qset,
			    struct urb *urb, int status)
{
	struct wusbhc *wusbhc = &whc->wusbhc;
	struct whc_urb *wurb = urb->hcpriv;

	usb_hcd_unlink_urb_from_ep(&wusbhc->usb_hcd, urb);
	/* Drop the lock as urb->complete() may enqueue another urb. */
	spin_unlock(&whc->lock);
	wusbhc_giveback_urb(wusbhc, urb, status);
	spin_lock(&whc->lock);

	kfree(wurb);
}