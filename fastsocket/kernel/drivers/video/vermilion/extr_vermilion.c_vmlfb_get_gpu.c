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
struct vml_par {int /*<<< orphan*/  gpu; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_INTEL ; 
 int /*<<< orphan*/  VML_DEVICE_GPU ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_enable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vml_mutex ; 

__attribute__((used)) static int vmlfb_get_gpu(struct vml_par *par)
{
	mutex_lock(&vml_mutex);

	par->gpu = pci_get_device(PCI_VENDOR_ID_INTEL, VML_DEVICE_GPU, NULL);

	if (!par->gpu) {
		mutex_unlock(&vml_mutex);
		return -ENODEV;
	}

	mutex_unlock(&vml_mutex);

	if (pci_enable_device(par->gpu) < 0)
		return -ENODEV;

	return 0;
}