#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_4__ {scalar_t__ controller; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct u132_platform_data {scalar_t__ vendor; scalar_t__ device; } ;
struct u132 {int going; TYPE_3__* platform_dev; int /*<<< orphan*/  sw_lock; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {scalar_t__ platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  OHCI_QUIRK_AMD756 ; 
 int /*<<< orphan*/  OHCI_QUIRK_ZFMICRO ; 
 scalar_t__ PCI_VENDOR_ID_AMD ; 
 scalar_t__ PCI_VENDOR_ID_COMPAQ ; 
 scalar_t__ PCI_VENDOR_ID_OPTI ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct u132* hcd_to_u132 (struct usb_hcd*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct platform_device* to_platform_device (scalar_t__) ; 
 int /*<<< orphan*/  u132_disable (struct u132*) ; 
 int u132_run (struct u132*) ; 

__attribute__((used)) static int u132_hcd_start(struct usb_hcd *hcd)
{
	struct u132 *u132 = hcd_to_u132(hcd);
	if (u132->going > 1) {
		dev_err(&u132->platform_dev->dev, "device has been removed %d\n"
			, u132->going);
		return -ENODEV;
	} else if (u132->going > 0) {
		dev_err(&u132->platform_dev->dev, "device is being removed\n");
		return -ESHUTDOWN;
	} else if (hcd->self.controller) {
		int retval;
		struct platform_device *pdev =
			to_platform_device(hcd->self.controller);
		u16 vendor = ((struct u132_platform_data *)
			(pdev->dev.platform_data))->vendor;
		u16 device = ((struct u132_platform_data *)
			(pdev->dev.platform_data))->device;
		mutex_lock(&u132->sw_lock);
		msleep(10);
		if (vendor == PCI_VENDOR_ID_AMD && device == 0x740c) {
			u132->flags = OHCI_QUIRK_AMD756;
		} else if (vendor == PCI_VENDOR_ID_OPTI && device == 0xc861) {
			dev_err(&u132->platform_dev->dev, "WARNING: OPTi workar"
				"ounds unavailable\n");
		} else if (vendor == PCI_VENDOR_ID_COMPAQ && device == 0xa0f8)
			u132->flags |= OHCI_QUIRK_ZFMICRO;
		retval = u132_run(u132);
		if (retval) {
			u132_disable(u132);
			u132->going = 1;
		}
		msleep(100);
		mutex_unlock(&u132->sw_lock);
		return retval;
	} else {
		dev_err(&u132->platform_dev->dev, "platform_device missing\n");
		return -ENODEV;
	}
}