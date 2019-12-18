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
struct iommu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  IOVMF_ALLOC ; 
 int /*<<< orphan*/  IOVMF_DA_ANON ; 
 int /*<<< orphan*/  IOVMF_DA_FIXED ; 
 int /*<<< orphan*/  IOVMF_HW_MASK ; 
 int /*<<< orphan*/  IOVMF_LINEAR ; 
 scalar_t__ IS_ERR_VALUE (int /*<<< orphan*/ ) ; 
 size_t PAGE_ALIGN (size_t) ; 
 int /*<<< orphan*/  __iommu_kmap (struct iommu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (size_t,int) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

u32 iommu_kmalloc(struct iommu *obj, u32 da, size_t bytes, u32 flags)
{
	void *va;
	u32 pa;

	if (!obj || !obj->dev || !bytes)
		return -EINVAL;

	bytes = PAGE_ALIGN(bytes);

	va = kmalloc(bytes, GFP_KERNEL | GFP_DMA);
	if (!va)
		return -ENOMEM;
	pa = virt_to_phys(va);

	flags &= IOVMF_HW_MASK;
	flags |= IOVMF_LINEAR;
	flags |= IOVMF_ALLOC;
	flags |= (da ? IOVMF_DA_FIXED : IOVMF_DA_ANON);

	da = __iommu_kmap(obj, da, pa, va, bytes, flags);
	if (IS_ERR_VALUE(da))
		kfree(va);

	return da;
}