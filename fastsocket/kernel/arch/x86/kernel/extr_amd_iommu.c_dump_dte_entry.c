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
typedef  size_t u16 ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 TYPE_1__* amd_iommu_dev_table ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_dte_entry(u16 devid)
{
	int i;

	for (i = 0; i < 8; ++i)
		pr_err("AMD-Vi: DTE[%d]: %08x\n", i,
			amd_iommu_dev_table[devid].data[i]);
}