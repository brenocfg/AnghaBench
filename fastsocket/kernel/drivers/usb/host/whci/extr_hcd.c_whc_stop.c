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
struct wusbhc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cluster_id; } ;
struct whc {scalar_t__ base; TYPE_1__* umc; } ;
struct usb_hcd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WUSBCMD_RUN ; 
 scalar_t__ WUSBINTR ; 
 scalar_t__ WUSBSTS ; 
 int /*<<< orphan*/  WUSBSTS_HCHALTED ; 
 int /*<<< orphan*/  le_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wusbhc* usb_hcd_to_wusbhc (struct usb_hcd*) ; 
 int /*<<< orphan*/  whc_write_wusbcmd (struct whc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  whci_wait_for (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  wusb_cluster_id_put (int /*<<< orphan*/ ) ; 
 struct whc* wusbhc_to_whc (struct wusbhc*) ; 

__attribute__((used)) static void whc_stop(struct usb_hcd *usb_hcd)
{
	struct wusbhc *wusbhc = usb_hcd_to_wusbhc(usb_hcd);
	struct whc *whc = wusbhc_to_whc(wusbhc);

	mutex_lock(&wusbhc->mutex);

	/* stop HC */
	le_writel(0, whc->base + WUSBINTR);
	whc_write_wusbcmd(whc, WUSBCMD_RUN, 0);
	whci_wait_for(&whc->umc->dev, whc->base + WUSBSTS,
		      WUSBSTS_HCHALTED, WUSBSTS_HCHALTED,
		      100, "HC to halt");

	wusb_cluster_id_put(wusbhc->cluster_id);

	mutex_unlock(&wusbhc->mutex);
}