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

/* Variables and functions */
 scalar_t__ dmar_disabled ; 
 scalar_t__ no_iommu ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 scalar_t__ swiotlb ; 
 int /*<<< orphan*/  tboot_enabled () ; 

int tboot_force_iommu(void)
{
	if (!tboot_enabled())
		return 0;

	if (no_iommu || swiotlb || dmar_disabled)
		pr_warning("Forcing Intel-IOMMU to enabled\n");

	dmar_disabled = 0;
#ifdef CONFIG_SWIOTLB
	swiotlb = 0;
#endif
	no_iommu = 0;

	return 1;
}