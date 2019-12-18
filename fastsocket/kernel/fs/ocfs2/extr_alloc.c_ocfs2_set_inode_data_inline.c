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
struct ocfs2_inode_info {int /*<<< orphan*/  ip_lock; int /*<<< orphan*/  ip_dyn_features; } ;
struct ocfs2_inline_data {void* id_count; } ;
struct TYPE_2__ {struct ocfs2_inline_data i_data; } ;
struct ocfs2_dinode {void* i_dyn_features; TYPE_1__ id2; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_INLINE_DATA_FL ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_max_inline_data_with_xattr (int /*<<< orphan*/ ,struct ocfs2_dinode*) ; 
 int /*<<< orphan*/  ocfs2_zero_dinode_id2_with_xattr (struct inode*,struct ocfs2_dinode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ocfs2_set_inode_data_inline(struct inode *inode, struct ocfs2_dinode *di)
{
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	struct ocfs2_inline_data *idata = &di->id2.i_data;

	spin_lock(&oi->ip_lock);
	oi->ip_dyn_features |= OCFS2_INLINE_DATA_FL;
	di->i_dyn_features = cpu_to_le16(oi->ip_dyn_features);
	spin_unlock(&oi->ip_lock);

	/*
	 * We clear the entire i_data structure here so that all
	 * fields can be properly initialized.
	 */
	ocfs2_zero_dinode_id2_with_xattr(inode, di);

	idata->id_count = cpu_to_le16(
			ocfs2_max_inline_data_with_xattr(inode->i_sb, di));
}