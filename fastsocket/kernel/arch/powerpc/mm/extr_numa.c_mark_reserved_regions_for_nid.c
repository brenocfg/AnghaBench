#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pglist_data {unsigned long node_start_pfn; unsigned long node_spanned_pages; } ;
struct node_active_region {unsigned long start_pfn; unsigned long end_pfn; int nid; } ;
struct TYPE_5__ {int cnt; TYPE_1__* region; } ;
struct TYPE_6__ {TYPE_2__ reserved; } ;
struct TYPE_4__ {unsigned long base; unsigned long size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOTMEM_DEFAULT ; 
 struct pglist_data* NODE_DATA (int) ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PFN_UP (unsigned long) ; 
 int /*<<< orphan*/  dbg (char*,unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  get_node_active_region (unsigned long,struct node_active_region*) ; 
 TYPE_3__ lmb ; 
 int /*<<< orphan*/  reserve_bootmem_node (struct pglist_data*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mark_reserved_regions_for_nid(int nid)
{
	struct pglist_data *node = NODE_DATA(nid);
	int i;

	for (i = 0; i < lmb.reserved.cnt; i++) {
		unsigned long physbase = lmb.reserved.region[i].base;
		unsigned long size = lmb.reserved.region[i].size;
		unsigned long start_pfn = physbase >> PAGE_SHIFT;
		unsigned long end_pfn = PFN_UP(physbase + size);
		struct node_active_region node_ar;
		unsigned long node_end_pfn = node->node_start_pfn +
					     node->node_spanned_pages;

		/*
		 * Check to make sure that this lmb.reserved area is
		 * within the bounds of the node that we care about.
		 * Checking the nid of the start and end points is not
		 * sufficient because the reserved area could span the
		 * entire node.
		 */
		if (end_pfn <= node->node_start_pfn ||
		    start_pfn >= node_end_pfn)
			continue;

		get_node_active_region(start_pfn, &node_ar);
		while (start_pfn < end_pfn &&
			node_ar.start_pfn < node_ar.end_pfn) {
			unsigned long reserve_size = size;
			/*
			 * if reserved region extends past active region
			 * then trim size to active region
			 */
			if (end_pfn > node_ar.end_pfn)
				reserve_size = (node_ar.end_pfn << PAGE_SHIFT)
					- physbase;
			/*
			 * Only worry about *this* node, others may not
			 * yet have valid NODE_DATA().
			 */
			if (node_ar.nid == nid) {
				dbg("reserve_bootmem %lx %lx nid=%d\n",
					physbase, reserve_size, node_ar.nid);
				reserve_bootmem_node(NODE_DATA(node_ar.nid),
						physbase, reserve_size,
						BOOTMEM_DEFAULT);
			}
			/*
			 * if reserved region is contained in the active region
			 * then done.
			 */
			if (end_pfn <= node_ar.end_pfn)
				break;

			/*
			 * reserved region extends past the active region
			 *   get next active region that contains this
			 *   reserved region
			 */
			start_pfn = node_ar.end_pfn;
			physbase = start_pfn << PAGE_SHIFT;
			size = size - reserve_size;
			get_node_active_region(start_pfn, &node_ar);
		}
	}
}