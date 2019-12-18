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
struct ocfs2_dinode {int /*<<< orphan*/  i_suballoc_bit; int /*<<< orphan*/  i_blkno; int /*<<< orphan*/  i_suballoc_slot; } ;
struct ocfs2_alloc_context {scalar_t__ ac_alloc_slot; scalar_t__ ac_last_group; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_2__ {scalar_t__ ip_last_used_slot; scalar_t__ ip_last_used_group; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (struct inode*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_which_suballoc_group (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ocfs2_init_inode_ac_group(struct inode *dir,
				      struct buffer_head *parent_fe_bh,
				      struct ocfs2_alloc_context *ac)
{
	struct ocfs2_dinode *fe = (struct ocfs2_dinode *)parent_fe_bh->b_data;
	/*
	 * Try to allocate inodes from some specific group.
	 *
	 * If the parent dir has recorded the last group used in allocation,
	 * cool, use it. Otherwise if we try to allocate new inode from the
	 * same slot the parent dir belongs to, use the same chunk.
	 *
	 * We are very careful here to avoid the mistake of setting
	 * ac_last_group to a group descriptor from a different (unlocked) slot.
	 */
	if (OCFS2_I(dir)->ip_last_used_group &&
	    OCFS2_I(dir)->ip_last_used_slot == ac->ac_alloc_slot)
		ac->ac_last_group = OCFS2_I(dir)->ip_last_used_group;
	else if (le16_to_cpu(fe->i_suballoc_slot) == ac->ac_alloc_slot)
		ac->ac_last_group = ocfs2_which_suballoc_group(
					le64_to_cpu(fe->i_blkno),
					le16_to_cpu(fe->i_suballoc_bit));
}