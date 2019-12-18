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
typedef  size_t u32 ;
struct scatterlist {size_t rd_sg_count; struct scatterlist* sg_table; } ;
struct rd_dev_sg_table {size_t rd_sg_count; struct rd_dev_sg_table* sg_table; } ;
struct rd_dev {size_t sg_table_count; struct scatterlist* sg_table_array; int /*<<< orphan*/  rd_dev_id; TYPE_1__* rd_host; } ;
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rd_host_id; } ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  kfree (struct scatterlist*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t,unsigned long) ; 
 struct page* sg_page (struct scatterlist*) ; 

__attribute__((used)) static void rd_release_device_space(struct rd_dev *rd_dev)
{
	u32 i, j, page_count = 0, sg_per_table;
	struct rd_dev_sg_table *sg_table;
	struct page *pg;
	struct scatterlist *sg;

	if (!rd_dev->sg_table_array || !rd_dev->sg_table_count)
		return;

	sg_table = rd_dev->sg_table_array;

	for (i = 0; i < rd_dev->sg_table_count; i++) {
		sg = sg_table[i].sg_table;
		sg_per_table = sg_table[i].rd_sg_count;

		for (j = 0; j < sg_per_table; j++) {
			pg = sg_page(&sg[j]);
			if (pg) {
				__free_page(pg);
				page_count++;
			}
		}

		kfree(sg);
	}

	pr_debug("CORE_RD[%u] - Released device space for Ramdisk"
		" Device ID: %u, pages %u in %u tables total bytes %lu\n",
		rd_dev->rd_host->rd_host_id, rd_dev->rd_dev_id, page_count,
		rd_dev->sg_table_count, (unsigned long)page_count * PAGE_SIZE);

	kfree(sg_table);
	rd_dev->sg_table_array = NULL;
	rd_dev->sg_table_count = 0;
}