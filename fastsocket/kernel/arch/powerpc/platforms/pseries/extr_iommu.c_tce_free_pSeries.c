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
typedef  int /*<<< orphan*/  u64 ;
struct iommu_table {scalar_t__ it_base; } ;

/* Variables and functions */

__attribute__((used)) static void tce_free_pSeries(struct iommu_table *tbl, long index, long npages)
{
	u64 *tcep;

	tcep = ((u64 *)tbl->it_base) + index;

	while (npages--)
		*(tcep++) = 0;
}