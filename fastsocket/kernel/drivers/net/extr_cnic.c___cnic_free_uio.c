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
struct cnic_uio_dev {int /*<<< orphan*/  pdev; int /*<<< orphan*/  cnic_uinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cnic_free_uio_rings (struct cnic_uio_dev*) ; 
 int /*<<< orphan*/  kfree (struct cnic_uio_dev*) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uio_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __cnic_free_uio(struct cnic_uio_dev *udev)
{
	uio_unregister_device(&udev->cnic_uinfo);

	__cnic_free_uio_rings(udev);

	pci_dev_put(udev->pdev);
	kfree(udev);
}