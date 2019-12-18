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
struct dmar_domain {scalar_t__ flags; int /*<<< orphan*/  iommu_bmp; } ;

/* Variables and functions */
 struct dmar_domain* alloc_domain_mem () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct dmar_domain *alloc_domain(void)
{
	struct dmar_domain *domain;

	domain = alloc_domain_mem();
	if (!domain)
		return NULL;

	memset(domain->iommu_bmp, 0, sizeof(domain->iommu_bmp));
	domain->flags = 0;

	return domain;
}