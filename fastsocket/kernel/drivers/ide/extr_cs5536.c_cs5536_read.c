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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MSR_IDE_CFG ; 
 scalar_t__ PCI_IDE_CFG ; 
 int pci_read_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdmsr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_msr ; 

__attribute__((used)) static int cs5536_read(struct pci_dev *pdev, int reg, u32 *val)
{
	if (unlikely(use_msr)) {
		u32 dummy;

		rdmsr(MSR_IDE_CFG + reg, *val, dummy);
		return 0;
	}

	return pci_read_config_dword(pdev, PCI_IDE_CFG + reg * 4, val);
}