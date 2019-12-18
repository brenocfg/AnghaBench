#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct TYPE_8__ {TYPE_1__* l_recs; } ;
struct TYPE_9__ {TYPE_2__ i_list; } ;
struct ocfs2_dinode {TYPE_3__ id2; int /*<<< orphan*/  i_clusters; } ;
struct inode {TYPE_4__* i_sb; } ;
struct buffer_head {int b_size; scalar_t__ b_data; int /*<<< orphan*/  b_page; } ;
typedef  int sector_t ;
struct TYPE_10__ {int s_blocksize_bits; } ;
struct TYPE_7__ {int /*<<< orphan*/  e_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  KM_USER0 ; 
 int /*<<< orphan*/  ML_ERROR ; 
 struct ocfs2_super* OCFS2_SB (TYPE_4__*) ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_jbd (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 void* kmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct inode*,unsigned long long,struct buffer_head*,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 scalar_t__ ocfs2_clusters_to_blocks (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_is_fast_symlink (struct inode*) ; 
 scalar_t__ ocfs2_inode_is_new (struct inode*) ; 
 int ocfs2_read_inode_block (struct inode*,struct buffer_head**) ; 
 struct buffer_head* sb_getblk (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 

__attribute__((used)) static int ocfs2_symlink_get_block(struct inode *inode, sector_t iblock,
				   struct buffer_head *bh_result, int create)
{
	int err = -EIO;
	int status;
	struct ocfs2_dinode *fe = NULL;
	struct buffer_head *bh = NULL;
	struct buffer_head *buffer_cache_bh = NULL;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	void *kaddr;

	mlog_entry("(0x%p, %llu, 0x%p, %d)\n", inode,
		   (unsigned long long)iblock, bh_result, create);

	BUG_ON(ocfs2_inode_is_fast_symlink(inode));

	if ((iblock << inode->i_sb->s_blocksize_bits) > PATH_MAX + 1) {
		mlog(ML_ERROR, "block offset > PATH_MAX: %llu",
		     (unsigned long long)iblock);
		goto bail;
	}

	status = ocfs2_read_inode_block(inode, &bh);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}
	fe = (struct ocfs2_dinode *) bh->b_data;

	if ((u64)iblock >= ocfs2_clusters_to_blocks(inode->i_sb,
						    le32_to_cpu(fe->i_clusters))) {
		mlog(ML_ERROR, "block offset is outside the allocated size: "
		     "%llu\n", (unsigned long long)iblock);
		goto bail;
	}

	/* We don't use the page cache to create symlink data, so if
	 * need be, copy it over from the buffer cache. */
	if (!buffer_uptodate(bh_result) && ocfs2_inode_is_new(inode)) {
		u64 blkno = le64_to_cpu(fe->id2.i_list.l_recs[0].e_blkno) +
			    iblock;
		buffer_cache_bh = sb_getblk(osb->sb, blkno);
		if (!buffer_cache_bh) {
			mlog(ML_ERROR, "couldn't getblock for symlink!\n");
			goto bail;
		}

		/* we haven't locked out transactions, so a commit
		 * could've happened. Since we've got a reference on
		 * the bh, even if it commits while we're doing the
		 * copy, the data is still good. */
		if (buffer_jbd(buffer_cache_bh)
		    && ocfs2_inode_is_new(inode)) {
			kaddr = kmap_atomic(bh_result->b_page, KM_USER0);
			if (!kaddr) {
				mlog(ML_ERROR, "couldn't kmap!\n");
				goto bail;
			}
			memcpy(kaddr + (bh_result->b_size * iblock),
			       buffer_cache_bh->b_data,
			       bh_result->b_size);
			kunmap_atomic(kaddr, KM_USER0);
			set_buffer_uptodate(bh_result);
		}
		brelse(buffer_cache_bh);
	}

	map_bh(bh_result, inode->i_sb,
	       le64_to_cpu(fe->id2.i_list.l_recs[0].e_blkno) + iblock);

	err = 0;

bail:
	brelse(bh);

	mlog_exit(err);
	return err;
}