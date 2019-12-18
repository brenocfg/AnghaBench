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
struct ocfs2_meta_lvb {void* lvb_igeneration; void* lvb_idynfeatures; void* lvb_iattr; void* lvb_imtime_packed; void* lvb_ictime_packed; void* lvb_iatime_packed; void* lvb_inlink; void* lvb_imode; void* lvb_igid; void* lvb_iuid; void* lvb_iclusters; void* lvb_isize; scalar_t__ lvb_version; } ;
struct ocfs2_lock_res {int /*<<< orphan*/  l_lksb; } ;
struct ocfs2_inode_info {int ip_flags; int /*<<< orphan*/  ip_dyn_features; int /*<<< orphan*/  ip_attr; int /*<<< orphan*/  ip_clusters; struct ocfs2_lock_res ip_inode_lockres; } ;
struct inode {int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;

/* Variables and functions */
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int OCFS2_INODE_DELETED ; 
 scalar_t__ OCFS2_LVB_VERSION ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_exit_void () ; 
 int /*<<< orphan*/  mlog_meta_lvb (int /*<<< orphan*/ ,struct ocfs2_lock_res*) ; 
 struct ocfs2_meta_lvb* ocfs2_dlm_lvb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_pack_timespec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __ocfs2_stuff_meta_lvb(struct inode *inode)
{
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	struct ocfs2_lock_res *lockres = &oi->ip_inode_lockres;
	struct ocfs2_meta_lvb *lvb;

	mlog_entry_void();

	lvb = ocfs2_dlm_lvb(&lockres->l_lksb);

	/*
	 * Invalidate the LVB of a deleted inode - this way other
	 * nodes are forced to go to disk and discover the new inode
	 * status.
	 */
	if (oi->ip_flags & OCFS2_INODE_DELETED) {
		lvb->lvb_version = 0;
		goto out;
	}

	lvb->lvb_version   = OCFS2_LVB_VERSION;
	lvb->lvb_isize	   = cpu_to_be64(i_size_read(inode));
	lvb->lvb_iclusters = cpu_to_be32(oi->ip_clusters);
	lvb->lvb_iuid      = cpu_to_be32(inode->i_uid);
	lvb->lvb_igid      = cpu_to_be32(inode->i_gid);
	lvb->lvb_imode     = cpu_to_be16(inode->i_mode);
	lvb->lvb_inlink    = cpu_to_be16(inode->i_nlink);
	lvb->lvb_iatime_packed  =
		cpu_to_be64(ocfs2_pack_timespec(&inode->i_atime));
	lvb->lvb_ictime_packed =
		cpu_to_be64(ocfs2_pack_timespec(&inode->i_ctime));
	lvb->lvb_imtime_packed =
		cpu_to_be64(ocfs2_pack_timespec(&inode->i_mtime));
	lvb->lvb_iattr    = cpu_to_be32(oi->ip_attr);
	lvb->lvb_idynfeatures = cpu_to_be16(oi->ip_dyn_features);
	lvb->lvb_igeneration = cpu_to_be32(inode->i_generation);

out:
	mlog_meta_lvb(0, lockres);

	mlog_exit_void();
}