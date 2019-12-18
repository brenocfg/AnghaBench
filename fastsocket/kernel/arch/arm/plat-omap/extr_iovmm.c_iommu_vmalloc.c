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
struct sg_table {int dummy; } ;
struct iommu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  IOVMF_ALLOC ; 
 int /*<<< orphan*/  IOVMF_DA_ANON ; 
 int /*<<< orphan*/  IOVMF_DA_FIXED ; 
 int /*<<< orphan*/  IOVMF_DISCONT ; 
 int /*<<< orphan*/  IOVMF_HW_MASK ; 
 scalar_t__ IS_ERR (struct sg_table*) ; 
 scalar_t__ IS_ERR_VALUE (int /*<<< orphan*/ ) ; 
 size_t PAGE_ALIGN (size_t) ; 
 int /*<<< orphan*/  PTR_ERR (struct sg_table*) ; 
 int /*<<< orphan*/  __iommu_vmap (struct iommu*,int /*<<< orphan*/ ,struct sg_table*,void*,size_t,int /*<<< orphan*/ ) ; 
 struct sg_table* sgtable_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sgtable_drain_vmalloc (struct sg_table*) ; 
 int /*<<< orphan*/  sgtable_fill_vmalloc (struct sg_table*,void*) ; 
 int /*<<< orphan*/  sgtable_free (struct sg_table*) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vmalloc (size_t) ; 

u32 iommu_vmalloc(struct iommu *obj, u32 da, size_t bytes, u32 flags)
{
	void *va;
	struct sg_table *sgt;

	if (!obj || !obj->dev || !bytes)
		return -EINVAL;

	bytes = PAGE_ALIGN(bytes);

	va = vmalloc(bytes);
	if (!va)
		return -ENOMEM;

	sgt = sgtable_alloc(bytes, flags);
	if (IS_ERR(sgt)) {
		da = PTR_ERR(sgt);
		goto err_sgt_alloc;
	}
	sgtable_fill_vmalloc(sgt, va);

	flags &= IOVMF_HW_MASK;
	flags |= IOVMF_DISCONT;
	flags |= IOVMF_ALLOC;
	flags |= (da ? IOVMF_DA_FIXED : IOVMF_DA_ANON);

	da = __iommu_vmap(obj, da, sgt, va, bytes, flags);
	if (IS_ERR_VALUE(da))
		goto err_iommu_vmap;

	return da;

err_iommu_vmap:
	sgtable_drain_vmalloc(sgt);
	sgtable_free(sgt);
err_sgt_alloc:
	vfree(va);
	return da;
}