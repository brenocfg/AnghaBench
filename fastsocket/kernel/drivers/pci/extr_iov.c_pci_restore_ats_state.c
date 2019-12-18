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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {TYPE_1__* ats; int /*<<< orphan*/  is_virtfn; } ;
struct TYPE_2__ {scalar_t__ pos; scalar_t__ stu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ PCI_ATS_CTRL ; 
 int /*<<< orphan*/  PCI_ATS_CTRL_ENABLE ; 
 int /*<<< orphan*/  PCI_ATS_CTRL_STU (scalar_t__) ; 
 scalar_t__ PCI_ATS_MIN_STU ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_ATS ; 
 int /*<<< orphan*/  pci_ats_enabled (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

void pci_restore_ats_state(struct pci_dev *dev)
{
	u16 ctrl;

	if (!pci_ats_enabled(dev))
		return;
	if (!pci_find_ext_capability(dev, PCI_EXT_CAP_ID_ATS))
		BUG();

	ctrl = PCI_ATS_CTRL_ENABLE;
	if (!dev->is_virtfn)
		ctrl |= PCI_ATS_CTRL_STU(dev->ats->stu - PCI_ATS_MIN_STU);

	pci_write_config_word(dev, dev->ats->pos + PCI_ATS_CTRL, ctrl);
}