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
 unsigned long cpuid_eax (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int dca_enabled_in_bios(struct pci_dev *pdev)
{
	/* CPUID level 9 returns DCA configuration */
	/* Bit 0 indicates DCA enabled by the BIOS */
	unsigned long cpuid_level_9;
	int res;

	cpuid_level_9 = cpuid_eax(9);
	res = test_bit(0, &cpuid_level_9);
	if (!res)
		dev_dbg(&pdev->dev, "DCA is disabled in BIOS\n");

	return res;
}