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
struct iommu_domain {struct dmar_domain* priv; } ;
struct dmar_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vm_domain_exit (struct dmar_domain*) ; 

__attribute__((used)) static void intel_iommu_domain_destroy(struct iommu_domain *domain)
{
	struct dmar_domain *dmar_domain = domain->priv;

	domain->priv = NULL;
	vm_domain_exit(dmar_domain);
}