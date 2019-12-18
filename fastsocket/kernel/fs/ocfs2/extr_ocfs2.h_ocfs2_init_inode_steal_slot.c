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
struct ocfs2_super {int /*<<< orphan*/  s_num_inodes_stolen; int /*<<< orphan*/  osb_lock; int /*<<< orphan*/  s_inode_steal_slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_INVALID_SLOT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ocfs2_init_inode_steal_slot(struct ocfs2_super *osb)
{
	spin_lock(&osb->osb_lock);
	osb->s_inode_steal_slot = OCFS2_INVALID_SLOT;
	spin_unlock(&osb->osb_lock);
	atomic_set(&osb->s_num_inodes_stolen, 0);
}