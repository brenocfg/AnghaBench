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
struct iova {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iommu_iova_cache ; 
 struct iova* iommu_kmem_cache_alloc (int /*<<< orphan*/ ) ; 

struct iova *alloc_iova_mem(void)
{
	return iommu_kmem_cache_alloc(iommu_iova_cache);
}