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
struct ocfs2_super {int /*<<< orphan*/  osb_lock; struct ocfs2_slot_info* slot_info; } ;
struct ocfs2_slot_info {int dummy; } ;

/* Variables and functions */
 int __ocfs2_node_num_to_slot (struct ocfs2_slot_info*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ocfs2_node_num_to_slot(struct ocfs2_super *osb, unsigned int node_num)
{
	int slot;
	struct ocfs2_slot_info *si = osb->slot_info;

	spin_lock(&osb->osb_lock);
	slot = __ocfs2_node_num_to_slot(si, node_num);
	spin_unlock(&osb->osb_lock);

	return slot;
}