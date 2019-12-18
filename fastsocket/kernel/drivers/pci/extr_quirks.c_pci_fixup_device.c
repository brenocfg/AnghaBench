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
typedef  enum pci_fixup_pass { ____Placeholder_pci_fixup_pass } pci_fixup_pass ;

/* Variables and functions */

void pci_fixup_device(enum pci_fixup_pass pass, struct pci_dev *dev) {}