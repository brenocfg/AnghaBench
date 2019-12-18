#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ocfs2_super {TYPE_3__* sb; int /*<<< orphan*/  fs_generation; int /*<<< orphan*/  slot_num; } ;
struct TYPE_8__ {void* l_count; } ;
struct TYPE_7__ {void* de_count; } ;
struct ocfs2_dx_root_block {TYPE_2__ dr_list; TYPE_1__ dr_entries; int /*<<< orphan*/  dr_flags; void* dr_free_blk; void* dr_num_entries; void* dr_dir_blkno; void* dr_blkno; void* dr_fs_generation; void* dr_suballoc_bit; void* dr_suballoc_slot; int /*<<< orphan*/  dr_signature; } ;
struct ocfs2_dir_block_trailer {int /*<<< orphan*/  db_free_rec_len; } ;
struct ocfs2_dinode {void* i_dyn_features; void* i_dx_root; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_blocknr; scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_10__ {int /*<<< orphan*/  ip_dyn_features; scalar_t__ ip_blkno; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_blocksize; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_DX_FLAG_INLINE ; 
 int /*<<< orphan*/  OCFS2_DX_ROOT_SIGNATURE ; 
 TYPE_6__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_INDEXED_DIR_FL ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_CREATE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ocfs2_dx_root_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_claim_metadata (struct ocfs2_super*,int /*<<< orphan*/ *,struct ocfs2_alloc_context*,int,int /*<<< orphan*/ *,unsigned int*,scalar_t__*) ; 
 int /*<<< orphan*/  ocfs2_dx_entries_per_root (TYPE_3__*) ; 
 int /*<<< orphan*/  ocfs2_extent_recs_per_dx_root (TYPE_3__*) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_access_dr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_set_new_buffer_uptodate (int /*<<< orphan*/ ,struct buffer_head*) ; 
 struct ocfs2_dir_block_trailer* ocfs2_trailer_from_bh (struct buffer_head*,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_getblk (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_dx_dir_attach_index(struct ocfs2_super *osb,
				     handle_t *handle, struct inode *dir,
				     struct buffer_head *di_bh,
				     struct buffer_head *dirdata_bh,
				     struct ocfs2_alloc_context *meta_ac,
				     int dx_inline, u32 num_entries,
				     struct buffer_head **ret_dx_root_bh)
{
	int ret;
	struct ocfs2_dinode *di = (struct ocfs2_dinode *) di_bh->b_data;
	u16 dr_suballoc_bit;
	u64 dr_blkno;
	unsigned int num_bits;
	struct buffer_head *dx_root_bh = NULL;
	struct ocfs2_dx_root_block *dx_root;
	struct ocfs2_dir_block_trailer *trailer =
		ocfs2_trailer_from_bh(dirdata_bh, dir->i_sb);

	ret = ocfs2_claim_metadata(osb, handle, meta_ac, 1, &dr_suballoc_bit,
				   &num_bits, &dr_blkno);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	mlog(0, "Dir %llu, attach new index block: %llu\n",
	     (unsigned long long)OCFS2_I(dir)->ip_blkno,
	     (unsigned long long)dr_blkno);

	dx_root_bh = sb_getblk(osb->sb, dr_blkno);
	if (dx_root_bh == NULL) {
		ret = -EIO;
		goto out;
	}
	ocfs2_set_new_buffer_uptodate(INODE_CACHE(dir), dx_root_bh);

	ret = ocfs2_journal_access_dr(handle, INODE_CACHE(dir), dx_root_bh,
				      OCFS2_JOURNAL_ACCESS_CREATE);
	if (ret < 0) {
		mlog_errno(ret);
		goto out;
	}

	dx_root = (struct ocfs2_dx_root_block *)dx_root_bh->b_data;
	memset(dx_root, 0, osb->sb->s_blocksize);
	strcpy(dx_root->dr_signature, OCFS2_DX_ROOT_SIGNATURE);
	dx_root->dr_suballoc_slot = cpu_to_le16(osb->slot_num);
	dx_root->dr_suballoc_bit = cpu_to_le16(dr_suballoc_bit);
	dx_root->dr_fs_generation = cpu_to_le32(osb->fs_generation);
	dx_root->dr_blkno = cpu_to_le64(dr_blkno);
	dx_root->dr_dir_blkno = cpu_to_le64(OCFS2_I(dir)->ip_blkno);
	dx_root->dr_num_entries = cpu_to_le32(num_entries);
	if (le16_to_cpu(trailer->db_free_rec_len))
		dx_root->dr_free_blk = cpu_to_le64(dirdata_bh->b_blocknr);
	else
		dx_root->dr_free_blk = cpu_to_le64(0);

	if (dx_inline) {
		dx_root->dr_flags |= OCFS2_DX_FLAG_INLINE;
		dx_root->dr_entries.de_count =
			cpu_to_le16(ocfs2_dx_entries_per_root(osb->sb));
	} else {
		dx_root->dr_list.l_count =
			cpu_to_le16(ocfs2_extent_recs_per_dx_root(osb->sb));
	}

	ret = ocfs2_journal_dirty(handle, dx_root_bh);
	if (ret)
		mlog_errno(ret);

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(dir), di_bh,
				      OCFS2_JOURNAL_ACCESS_CREATE);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	di->i_dx_root = cpu_to_le64(dr_blkno);

	OCFS2_I(dir)->ip_dyn_features |= OCFS2_INDEXED_DIR_FL;
	di->i_dyn_features = cpu_to_le16(OCFS2_I(dir)->ip_dyn_features);

	ret = ocfs2_journal_dirty(handle, di_bh);
	if (ret)
		mlog_errno(ret);

	*ret_dx_root_bh = dx_root_bh;
	dx_root_bh = NULL;

out:
	brelse(dx_root_bh);
	return ret;
}