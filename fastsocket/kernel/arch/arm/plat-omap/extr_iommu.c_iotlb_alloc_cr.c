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
struct iotlb_entry {int dummy; } ;
struct iommu {int dummy; } ;
struct cr_regs {int dummy; } ;
struct TYPE_2__ {struct cr_regs* (* alloc_cr ) (struct iommu*,struct iotlb_entry*) ;} ;

/* Variables and functions */
 TYPE_1__* arch_iommu ; 
 struct cr_regs* stub1 (struct iommu*,struct iotlb_entry*) ; 

__attribute__((used)) static inline struct cr_regs *iotlb_alloc_cr(struct iommu *obj,
					     struct iotlb_entry *e)
{
	if (!e)
		return NULL;

	return arch_iommu->alloc_cr(obj, e);
}