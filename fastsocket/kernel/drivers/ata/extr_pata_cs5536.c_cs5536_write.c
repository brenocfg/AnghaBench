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

/* Variables and functions */
 int /*<<< orphan*/ * msr_reg ; 
 int /*<<< orphan*/ * pci_reg ; 
 int pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_msr ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cs5536_write(struct pci_dev *pdev, int reg, int val)
{
	if (unlikely(use_msr)) {
		wrmsr(msr_reg[reg], val, 0);
		return 0;
	}

	return pci_write_config_dword(pdev, pci_reg[reg], val);
}