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
struct page {int dummy; } ;
struct hstate {int dummy; } ;
typedef  int /*<<< orphan*/  nodemask_t ;

/* Variables and functions */
 int /*<<< orphan*/  HTLB_BUDDY_PGALLOC ; 
 int /*<<< orphan*/  HTLB_BUDDY_PGALLOC_FAIL ; 
 struct page* alloc_fresh_huge_page_node (struct hstate*,int) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int hstate_next_node_to_alloc (struct hstate*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alloc_fresh_huge_page(struct hstate *h, nodemask_t *nodes_allowed)
{
	struct page *page;
	int start_nid;
	int next_nid;
	int ret = 0;

	start_nid = hstate_next_node_to_alloc(h, nodes_allowed);
	next_nid = start_nid;

	do {
		page = alloc_fresh_huge_page_node(h, next_nid);
		if (page) {
			ret = 1;
			break;
		}
		next_nid = hstate_next_node_to_alloc(h, nodes_allowed);
	} while (next_nid != start_nid);

	if (ret)
		count_vm_event(HTLB_BUDDY_PGALLOC);
	else
		count_vm_event(HTLB_BUDDY_PGALLOC_FAIL);

	return ret;
}