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
typedef  int u64 ;
struct iommu_table {scalar_t__ it_index; } ;

/* Variables and functions */
 scalar_t__ __get_SP () ; 
 int /*<<< orphan*/  current ; 
 int plpar_tce_stuff (int,int,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 scalar_t__ printk_ratelimit () ; 
 int /*<<< orphan*/  show_stack (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void tce_freemulti_pSeriesLP(struct iommu_table *tbl, long tcenum, long npages)
{
	u64 rc;

	rc = plpar_tce_stuff((u64)tbl->it_index, (u64)tcenum << 12, 0, npages);

	if (rc && printk_ratelimit()) {
		printk("tce_freemulti_pSeriesLP: plpar_tce_stuff failed\n");
		printk("\trc      = %lld\n", rc);
		printk("\tindex   = 0x%llx\n", (u64)tbl->it_index);
		printk("\tnpages  = 0x%llx\n", (u64)npages);
		show_stack(current, (unsigned long *)__get_SP());
	}
}