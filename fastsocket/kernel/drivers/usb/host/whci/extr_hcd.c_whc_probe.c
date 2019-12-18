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
struct wusbhc {scalar_t__ ports_max; int /*<<< orphan*/  uwb_rc; int /*<<< orphan*/  set_gtk; int /*<<< orphan*/  set_ptk; int /*<<< orphan*/  set_num_dnts; int /*<<< orphan*/  bwa_set; int /*<<< orphan*/  dev_info_set; int /*<<< orphan*/  mmcie_rm; int /*<<< orphan*/  mmcie_add; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  mmcies_max; struct device* dev; } ;
struct whc {scalar_t__ n_devices; struct umc_dev* umc; int /*<<< orphan*/  n_mmc_ies; } ;
struct TYPE_2__ {int sg_tablesize; } ;
struct usb_hcd {int wireless; TYPE_1__ self; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct umc_dev {int /*<<< orphan*/  irq; struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ USB_MAXCHILDREN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,scalar_t__) ; 
 int usb_add_hcd (struct usb_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (int /*<<< orphan*/ *,struct device*,char*) ; 
 struct wusbhc* usb_hcd_to_wusbhc (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  uwb_rc_get_by_grandpa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwb_rc_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  whc_bwa_set ; 
 int /*<<< orphan*/  whc_clean_up (struct whc*) ; 
 int /*<<< orphan*/  whc_dbg_init (struct whc*) ; 
 int /*<<< orphan*/  whc_dev_info_set ; 
 int /*<<< orphan*/  whc_hc_driver ; 
 int whc_init (struct whc*) ; 
 int /*<<< orphan*/  whc_mmcie_add ; 
 int /*<<< orphan*/  whc_mmcie_rm ; 
 int /*<<< orphan*/  whc_set_gtk ; 
 int /*<<< orphan*/  whc_set_num_dnts ; 
 int /*<<< orphan*/  whc_set_ptk ; 
 int /*<<< orphan*/  whc_wusbhc_start ; 
 int /*<<< orphan*/  whc_wusbhc_stop ; 
 int wusbhc_b_create (struct wusbhc*) ; 
 int wusbhc_create (struct wusbhc*) ; 
 int /*<<< orphan*/  wusbhc_destroy (struct wusbhc*) ; 
 struct whc* wusbhc_to_whc (struct wusbhc*) ; 

__attribute__((used)) static int whc_probe(struct umc_dev *umc)
{
	int ret = -ENOMEM;
	struct usb_hcd *usb_hcd;
	struct wusbhc *wusbhc = NULL;
	struct whc *whc = NULL;
	struct device *dev = &umc->dev;

	usb_hcd = usb_create_hcd(&whc_hc_driver, dev, "whci");
	if (usb_hcd == NULL) {
		dev_err(dev, "unable to create hcd\n");
		goto error;
	}

	usb_hcd->wireless = 1;
	usb_hcd->self.sg_tablesize = 2048; /* somewhat arbitrary */

	wusbhc = usb_hcd_to_wusbhc(usb_hcd);
	whc = wusbhc_to_whc(wusbhc);
	whc->umc = umc;

	ret = whc_init(whc);
	if (ret)
		goto error;

	wusbhc->dev = dev;
	wusbhc->uwb_rc = uwb_rc_get_by_grandpa(umc->dev.parent);
	if (!wusbhc->uwb_rc) {
		ret = -ENODEV;
		dev_err(dev, "cannot get radio controller\n");
		goto error;
	}

	if (whc->n_devices > USB_MAXCHILDREN) {
		dev_warn(dev, "USB_MAXCHILDREN too low for WUSB adapter (%u ports)\n",
			 whc->n_devices);
		wusbhc->ports_max = USB_MAXCHILDREN;
	} else
		wusbhc->ports_max = whc->n_devices;
	wusbhc->mmcies_max      = whc->n_mmc_ies;
	wusbhc->start           = whc_wusbhc_start;
	wusbhc->stop            = whc_wusbhc_stop;
	wusbhc->mmcie_add       = whc_mmcie_add;
	wusbhc->mmcie_rm        = whc_mmcie_rm;
	wusbhc->dev_info_set    = whc_dev_info_set;
	wusbhc->bwa_set         = whc_bwa_set;
	wusbhc->set_num_dnts    = whc_set_num_dnts;
	wusbhc->set_ptk         = whc_set_ptk;
	wusbhc->set_gtk         = whc_set_gtk;

	ret = wusbhc_create(wusbhc);
	if (ret)
		goto error_wusbhc_create;

	ret = usb_add_hcd(usb_hcd, whc->umc->irq, IRQF_SHARED);
	if (ret) {
		dev_err(dev, "cannot add HCD: %d\n", ret);
		goto error_usb_add_hcd;
	}

	ret = wusbhc_b_create(wusbhc);
	if (ret) {
		dev_err(dev, "WUSBHC phase B setup failed: %d\n", ret);
		goto error_wusbhc_b_create;
	}

	whc_dbg_init(whc);

	return 0;

error_wusbhc_b_create:
	usb_remove_hcd(usb_hcd);
error_usb_add_hcd:
	wusbhc_destroy(wusbhc);
error_wusbhc_create:
	uwb_rc_put(wusbhc->uwb_rc);
error:
	whc_clean_up(whc);
	if (usb_hcd)
		usb_put_hcd(usb_hcd);
	return ret;
}