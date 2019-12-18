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
struct pci_dev {int dummy; } ;
typedef  enum pci_bar_type { ____Placeholder_pci_bar_type } pci_bar_type ;

/* Variables and functions */

__attribute__((used)) static inline int pci_iov_resource_bar(struct pci_dev *dev, int resno,
				       enum pci_bar_type *type)
{
	return 0;
}