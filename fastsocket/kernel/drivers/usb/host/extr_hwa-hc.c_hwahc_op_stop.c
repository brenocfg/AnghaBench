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
struct wusbhc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cluster_id; } ;
struct usb_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wusbhc* usb_hcd_to_wusbhc (struct usb_hcd*) ; 
 int /*<<< orphan*/  wusb_cluster_id_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hwahc_op_stop(struct usb_hcd *usb_hcd)
{
	struct wusbhc *wusbhc = usb_hcd_to_wusbhc(usb_hcd);

	mutex_lock(&wusbhc->mutex);
	wusb_cluster_id_put(wusbhc->cluster_id);
	mutex_unlock(&wusbhc->mutex);
}