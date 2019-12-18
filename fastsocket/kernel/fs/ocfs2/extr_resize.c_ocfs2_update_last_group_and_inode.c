#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct ocfs2_super {int s_clustersize_bits; int /*<<< orphan*/  sb; } ;
struct ocfs2_group_desc {int /*<<< orphan*/  bg_free_bits_count; int /*<<< orphan*/  bg_bits; int /*<<< orphan*/  bg_chain; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_used; int /*<<< orphan*/  i_total; } ;
struct TYPE_7__ {TYPE_2__ bitmap1; } ;
struct ocfs2_chain_list {struct ocfs2_chain_rec* cl_recs; int /*<<< orphan*/  cl_cpg; int /*<<< orphan*/  cl_bpc; } ;
struct TYPE_5__ {struct ocfs2_chain_list i_chain; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_clusters; TYPE_3__ id1; TYPE_1__ id2; } ;
struct ocfs2_chain_rec {int /*<<< orphan*/  c_free; int /*<<< orphan*/  c_total; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_8__ {int /*<<< orphan*/  ip_lock; int /*<<< orphan*/  ip_clusters; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_FEATURE_COMPAT_BACKUP_SB ; 
 scalar_t__ OCFS2_HAS_COMPAT_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_entry (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_calc_new_backup_super (struct inode*,struct ocfs2_group_desc*,int,int /*<<< orphan*/ ,int,int) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_access_gd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_update_last_group_and_inode(handle_t *handle,
					     struct inode *bm_inode,
					     struct buffer_head *bm_bh,
					     struct buffer_head *group_bh,
					     u32 first_new_cluster,
					     int new_clusters)
{
	int ret = 0;
	struct ocfs2_super *osb = OCFS2_SB(bm_inode->i_sb);
	struct ocfs2_dinode *fe = (struct ocfs2_dinode *) bm_bh->b_data;
	struct ocfs2_chain_list *cl = &fe->id2.i_chain;
	struct ocfs2_chain_rec *cr;
	struct ocfs2_group_desc *group;
	u16 chain, num_bits, backups = 0;
	u16 cl_bpc = le16_to_cpu(cl->cl_bpc);
	u16 cl_cpg = le16_to_cpu(cl->cl_cpg);

	mlog_entry("(new_clusters=%d, first_new_cluster = %u)\n",
		   new_clusters, first_new_cluster);

	ret = ocfs2_journal_access_gd(handle, INODE_CACHE(bm_inode),
				      group_bh, OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret < 0) {
		mlog_errno(ret);
		goto out;
	}

	group = (struct ocfs2_group_desc *)group_bh->b_data;

	/* update the group first. */
	num_bits = new_clusters * cl_bpc;
	le16_add_cpu(&group->bg_bits, num_bits);
	le16_add_cpu(&group->bg_free_bits_count, num_bits);

	/*
	 * check whether there are some new backup superblocks exist in
	 * this group and update the group bitmap accordingly.
	 */
	if (OCFS2_HAS_COMPAT_FEATURE(osb->sb,
				     OCFS2_FEATURE_COMPAT_BACKUP_SB)) {
		backups = ocfs2_calc_new_backup_super(bm_inode,
						     group,
						     new_clusters,
						     first_new_cluster,
						     cl_cpg, 1);
		le16_add_cpu(&group->bg_free_bits_count, -1 * backups);
	}

	ret = ocfs2_journal_dirty(handle, group_bh);
	if (ret < 0) {
		mlog_errno(ret);
		goto out_rollback;
	}

	/* update the inode accordingly. */
	ret = ocfs2_journal_access_di(handle, INODE_CACHE(bm_inode), bm_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret < 0) {
		mlog_errno(ret);
		goto out_rollback;
	}

	chain = le16_to_cpu(group->bg_chain);
	cr = (&cl->cl_recs[chain]);
	le32_add_cpu(&cr->c_total, num_bits);
	le32_add_cpu(&cr->c_free, num_bits);
	le32_add_cpu(&fe->id1.bitmap1.i_total, num_bits);
	le32_add_cpu(&fe->i_clusters, new_clusters);

	if (backups) {
		le32_add_cpu(&cr->c_free, -1 * backups);
		le32_add_cpu(&fe->id1.bitmap1.i_used, backups);
	}

	spin_lock(&OCFS2_I(bm_inode)->ip_lock);
	OCFS2_I(bm_inode)->ip_clusters = le32_to_cpu(fe->i_clusters);
	le64_add_cpu(&fe->i_size, new_clusters << osb->s_clustersize_bits);
	spin_unlock(&OCFS2_I(bm_inode)->ip_lock);
	i_size_write(bm_inode, le64_to_cpu(fe->i_size));

	ocfs2_journal_dirty(handle, bm_bh);

out_rollback:
	if (ret < 0) {
		ocfs2_calc_new_backup_super(bm_inode,
					    group,
					    new_clusters,
					    first_new_cluster,
					    cl_cpg, 0);
		le16_add_cpu(&group->bg_free_bits_count, backups);
		le16_add_cpu(&group->bg_bits, -1 * num_bits);
		le16_add_cpu(&group->bg_free_bits_count, -1 * num_bits);
	}
out:
	mlog_exit(ret);
	return ret;
}