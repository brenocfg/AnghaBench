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
struct dmar_domain {int agaw; int /*<<< orphan*/  iommu_bmp; } ;
struct TYPE_2__ {int agaw; } ;

/* Variables and functions */
 int find_first_bit (int /*<<< orphan*/ ,int) ; 
 int find_next_bit (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__** g_iommus ; 
 int g_num_of_iommus ; 

__attribute__((used)) static int vm_domain_min_agaw(struct dmar_domain *domain)
{
	int i;
	int min_agaw = domain->agaw;

	i = find_first_bit(domain->iommu_bmp, g_num_of_iommus);
	for (; i < g_num_of_iommus; ) {
		if (min_agaw > g_iommus[i]->agaw)
			min_agaw = g_iommus[i]->agaw;

		i = find_next_bit(domain->iommu_bmp, g_num_of_iommus, i+1);
	}

	return min_agaw;
}