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
struct dmar_domain {int iommu_coherency; int /*<<< orphan*/  iommu_bmp; } ;
struct TYPE_2__ {int /*<<< orphan*/  ecap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ecap_coherent (int /*<<< orphan*/ ) ; 
 int find_first_bit (int /*<<< orphan*/ ,int) ; 
 int find_next_bit (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__** g_iommus ; 
 int g_num_of_iommus ; 

__attribute__((used)) static void domain_update_iommu_coherency(struct dmar_domain *domain)
{
	int i;

	i = find_first_bit(domain->iommu_bmp, g_num_of_iommus);

	domain->iommu_coherency = i < g_num_of_iommus ? 1 : 0;

	for (; i < g_num_of_iommus; ) {
		if (!ecap_coherent(g_iommus[i]->ecap)) {
			domain->iommu_coherency = 0;
			break;
		}
		i = find_next_bit(domain->iommu_bmp, g_num_of_iommus, i+1);
	}
}