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
struct ldc_mtable_entry {int dummy; } ;
struct TYPE_2__ {unsigned long limit; int /*<<< orphan*/ * map; } ;
struct ldc_iommu {TYPE_1__ arena; int /*<<< orphan*/ * page_table; } ;
struct ldc_channel {int /*<<< orphan*/  id; struct ldc_iommu iommu; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages (unsigned long,unsigned long) ; 
 unsigned long get_order (unsigned long) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sun4v_ldc_set_map_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ldc_iommu_release(struct ldc_channel *lp)
{
	struct ldc_iommu *iommu = &lp->iommu;
	unsigned long num_tsb_entries, tsbsize, order;

	(void) sun4v_ldc_set_map_table(lp->id, 0, 0);

	num_tsb_entries = iommu->arena.limit;
	tsbsize = num_tsb_entries * sizeof(struct ldc_mtable_entry);
	order = get_order(tsbsize);

	free_pages((unsigned long) iommu->page_table, order);
	iommu->page_table = NULL;

	kfree(iommu->arena.map);
	iommu->arena.map = NULL;
}