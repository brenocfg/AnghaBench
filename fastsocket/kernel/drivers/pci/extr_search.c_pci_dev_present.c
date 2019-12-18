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
struct pci_device_id {scalar_t__ class_mask; scalar_t__ subvendor; scalar_t__ vendor; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 struct pci_dev* pci_get_dev_by_id (struct pci_device_id const*,int /*<<< orphan*/ *) ; 

int pci_dev_present(const struct pci_device_id *ids)
{
	struct pci_dev *found = NULL;

	WARN_ON(in_interrupt());
	while (ids->vendor || ids->subvendor || ids->class_mask) {
		found = pci_get_dev_by_id(ids, NULL);
		if (found)
			goto exit;
		ids++;
	}
exit:
	if (found)
		return 1;
	return 0;
}