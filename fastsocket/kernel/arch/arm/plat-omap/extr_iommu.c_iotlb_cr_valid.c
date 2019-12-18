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
struct cr_regs {int dummy; } ;
struct TYPE_2__ {int (* cr_valid ) (struct cr_regs*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* arch_iommu ; 
 int stub1 (struct cr_regs*) ; 

__attribute__((used)) static inline int iotlb_cr_valid(struct cr_regs *cr)
{
	if (!cr)
		return -EINVAL;

	return arch_iommu->cr_valid(cr);
}