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
struct pci_dev {int subsystem_vendor; int subsystem_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  cable_dmi_table ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ali_cable_override(struct pci_dev *pdev)
{
	/* Fujitsu P2000 */
	if (pdev->subsystem_vendor == 0x10CF &&
	    pdev->subsystem_device == 0x10AF)
		return 1;

	/* Mitac 8317 (Winbook-A) and relatives */
	if (pdev->subsystem_vendor == 0x1071 &&
	    pdev->subsystem_device == 0x8317)
		return 1;

	/* Systems by DMI */
	if (dmi_check_system(cable_dmi_table))
		return 1;

	return 0;
}