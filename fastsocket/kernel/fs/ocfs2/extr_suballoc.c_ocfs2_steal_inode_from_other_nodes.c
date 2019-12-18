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
struct ocfs2_super {scalar_t__ slot_num; int max_slots; } ;
struct ocfs2_alloc_context {int dummy; } ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  INODE_ALLOC_SYSTEM_INODE ; 
 int /*<<< orphan*/  NOT_ALLOC_NEW_GROUP ; 
 scalar_t__ OCFS2_INVALID_SLOT ; 
 int /*<<< orphan*/  ocfs2_free_ac_resource (struct ocfs2_alloc_context*) ; 
 scalar_t__ ocfs2_get_inode_steal_slot (struct ocfs2_super*) ; 
 int ocfs2_reserve_suballoc_bits (struct ocfs2_super*,struct ocfs2_alloc_context*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_set_inode_steal_slot (struct ocfs2_super*,scalar_t__) ; 

__attribute__((used)) static int ocfs2_steal_inode_from_other_nodes(struct ocfs2_super *osb,
					      struct ocfs2_alloc_context *ac)
{
	int i, status = -ENOSPC;
	s16 slot = ocfs2_get_inode_steal_slot(osb);

	/* Start to steal inodes from the first slot after ours. */
	if (slot == OCFS2_INVALID_SLOT)
		slot = osb->slot_num + 1;

	for (i = 0; i < osb->max_slots; i++, slot++) {
		if (slot == osb->max_slots)
			slot = 0;

		if (slot == osb->slot_num)
			continue;

		status = ocfs2_reserve_suballoc_bits(osb, ac,
						     INODE_ALLOC_SYSTEM_INODE,
						     slot, NULL,
						     NOT_ALLOC_NEW_GROUP);
		if (status >= 0) {
			ocfs2_set_inode_steal_slot(osb, slot);
			break;
		}

		ocfs2_free_ac_resource(ac);
	}

	return status;
}