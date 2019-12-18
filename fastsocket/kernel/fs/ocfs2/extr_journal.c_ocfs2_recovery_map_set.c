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
struct ocfs2_super {size_t max_slots; int /*<<< orphan*/  osb_lock; struct ocfs2_recovery_map* recovery_map; } ;
struct ocfs2_recovery_map {size_t rm_used; unsigned int* rm_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ __ocfs2_recovery_map_test (struct ocfs2_super*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_recovery_map_set(struct ocfs2_super *osb,
				  unsigned int node_num)
{
	struct ocfs2_recovery_map *rm = osb->recovery_map;

	spin_lock(&osb->osb_lock);
	if (__ocfs2_recovery_map_test(osb, node_num)) {
		spin_unlock(&osb->osb_lock);
		return 1;
	}

	/* XXX: Can this be exploited? Not from o2dlm... */
	BUG_ON(rm->rm_used >= osb->max_slots);

	rm->rm_entries[rm->rm_used] = node_num;
	rm->rm_used++;
	spin_unlock(&osb->osb_lock);

	return 0;
}