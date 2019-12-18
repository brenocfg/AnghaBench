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
 int /*<<< orphan*/  IOVMF_DA_ANON ; 
 int /*<<< orphan*/  IOVMF_DA_FIXED ; 
 int /*<<< orphan*/  IOVMF_HW_MASK ; 
 int /*<<< orphan*/  IOVMF_LINEAR ; 
 int /*<<< orphan*/  IOVMF_MMIO ; 
 scalar_t__ IS_ERR_VALUE (int /*<<< orphan*/ ) ; 
 size_t PAGE_ALIGN (size_t) ; 
 int /*<<< orphan*/  __iommu_kmap (struct iommu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 
 void* ioremap (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  iounmap (void*) ; 

u32 iommu_kmap(struct iommu *obj, u32 da, u32 pa, size_t bytes,
		 u32 flags)
{
	void *va;

	if (!obj || !obj->dev || !bytes)
		return -EINVAL;

	bytes = PAGE_ALIGN(bytes);

	va = ioremap(pa, bytes);
	if (!va)
		return -ENOMEM;

	flags &= IOVMF_HW_MASK;
	flags |= IOVMF_LINEAR;
	flags |= IOVMF_MMIO;
	flags |= (da ? IOVMF_DA_FIXED : IOVMF_DA_ANON);

	da = __iommu_kmap(obj, da, pa, va, bytes, flags);
	if (IS_ERR_VALUE(da))
		iounmap(va);

	return da;
}