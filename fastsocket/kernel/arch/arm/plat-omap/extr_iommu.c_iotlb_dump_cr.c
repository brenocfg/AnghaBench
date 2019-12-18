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
struct iommu {int dummy; } ;
struct cr_regs {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* dump_cr ) (struct iommu*,struct cr_regs*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__* arch_iommu ; 
 int /*<<< orphan*/  stub1 (struct iommu*,struct cr_regs*,char*) ; 

__attribute__((used)) static inline ssize_t iotlb_dump_cr(struct iommu *obj, struct cr_regs *cr,
				    char *buf)
{
	BUG_ON(!cr || !buf);

	return arch_iommu->dump_cr(obj, cr, buf);
}