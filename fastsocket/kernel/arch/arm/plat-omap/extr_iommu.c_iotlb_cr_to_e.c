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
struct cr_regs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cr_to_e ) (struct cr_regs*,struct iotlb_entry*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__* arch_iommu ; 
 int /*<<< orphan*/  stub1 (struct cr_regs*,struct iotlb_entry*) ; 

void iotlb_cr_to_e(struct cr_regs *cr, struct iotlb_entry *e)
{
	BUG_ON(!cr || !e);

	arch_iommu->cr_to_e(cr, e);
}