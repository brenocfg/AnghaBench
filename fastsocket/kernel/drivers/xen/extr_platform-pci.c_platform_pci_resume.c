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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  callback_via ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ xen_have_vector_callback ; 
 int xen_set_callback_via (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int platform_pci_resume(struct pci_dev *pdev)
{
	int err;
	if (xen_have_vector_callback)
		return 0;
	err = xen_set_callback_via(callback_via);
	if (err) {
		dev_err(&pdev->dev, "platform_pci_resume failure!\n");
		return err;
	}
	return 0;
}