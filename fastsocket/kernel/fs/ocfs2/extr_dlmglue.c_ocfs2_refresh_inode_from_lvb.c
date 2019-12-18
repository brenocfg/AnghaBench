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
struct ocfs2_meta_lvb {int /*<<< orphan*/  lvb_ictime_packed; int /*<<< orphan*/  lvb_imtime_packed; int /*<<< orphan*/  lvb_iatime_packed; int /*<<< orphan*/  lvb_inlink; int /*<<< orphan*/  lvb_imode; int /*<<< orphan*/  lvb_igid; int /*<<< orphan*/  lvb_iuid; int /*<<< orphan*/  lvb_idynfeatures; int /*<<< orphan*/  lvb_iattr; int /*<<< orphan*/  lvb_isize; int /*<<< orphan*/  lvb_iclusters; } ;
struct ocfs2_lock_res {int /*<<< orphan*/  l_lksb; } ;
struct ocfs2_inode_info {int /*<<< orphan*/  ip_lock; void* ip_clusters; void* ip_dyn_features; void* ip_attr; struct ocfs2_lock_res ip_inode_lockres; } ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; void* i_nlink; void* i_mode; void* i_gid; void* i_uid; scalar_t__ i_blocks; } ;

/* Variables and functions */
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 scalar_t__ S_ISLNK (void*) ; 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_exit_void () ; 
 int /*<<< orphan*/  mlog_meta_lvb (int /*<<< orphan*/ ,struct ocfs2_lock_res*) ; 
 struct ocfs2_meta_lvb* ocfs2_dlm_lvb (int /*<<< orphan*/ *) ; 
 scalar_t__ ocfs2_inode_sector_count (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_set_inode_flags (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_unpack_timespec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_refresh_inode_from_lvb(struct inode *inode)
{
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	struct ocfs2_lock_res *lockres = &oi->ip_inode_lockres;
	struct ocfs2_meta_lvb *lvb;

	mlog_entry_void();

	mlog_meta_lvb(0, lockres);

	lvb = ocfs2_dlm_lvb(&lockres->l_lksb);

	/* We're safe here without the lockres lock... */
	spin_lock(&oi->ip_lock);
	oi->ip_clusters = be32_to_cpu(lvb->lvb_iclusters);
	i_size_write(inode, be64_to_cpu(lvb->lvb_isize));

	oi->ip_attr = be32_to_cpu(lvb->lvb_iattr);
	oi->ip_dyn_features = be16_to_cpu(lvb->lvb_idynfeatures);
	ocfs2_set_inode_flags(inode);

	/* fast-symlinks are a special case */
	if (S_ISLNK(inode->i_mode) && !oi->ip_clusters)
		inode->i_blocks = 0;
	else
		inode->i_blocks = ocfs2_inode_sector_count(inode);

	inode->i_uid     = be32_to_cpu(lvb->lvb_iuid);
	inode->i_gid     = be32_to_cpu(lvb->lvb_igid);
	inode->i_mode    = be16_to_cpu(lvb->lvb_imode);
	inode->i_nlink   = be16_to_cpu(lvb->lvb_inlink);
	ocfs2_unpack_timespec(&inode->i_atime,
			      be64_to_cpu(lvb->lvb_iatime_packed));
	ocfs2_unpack_timespec(&inode->i_mtime,
			      be64_to_cpu(lvb->lvb_imtime_packed));
	ocfs2_unpack_timespec(&inode->i_ctime,
			      be64_to_cpu(lvb->lvb_ictime_packed));
	spin_unlock(&oi->ip_lock);

	mlog_exit_void();
}