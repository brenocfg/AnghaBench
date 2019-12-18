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
typedef  int u64 ;
struct super_block {int s_blocksize; int s_blocksize_bits; } ;
struct ocfs2_super {struct super_block* sb; } ;
struct inode {scalar_t__ i_blocks; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  ip_clusters; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_CREATE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int i_size_read (struct inode*) ; 
 struct buffer_head** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct buffer_head**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_entry (char*,unsigned long long,int,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_clusters_to_bytes (struct super_block*,int /*<<< orphan*/ ) ; 
 int ocfs2_extent_map_get_blocks (struct inode*,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *) ; 
 int ocfs2_journal_access (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_set_new_buffer_uptodate (int /*<<< orphan*/ ,struct buffer_head*) ; 
 struct buffer_head* sb_getblk (struct super_block*,int) ; 

__attribute__((used)) static int ocfs2_create_symlink_data(struct ocfs2_super *osb,
				     handle_t *handle,
				     struct inode *inode,
				     const char *symname)
{
	struct buffer_head **bhs = NULL;
	const char *c;
	struct super_block *sb = osb->sb;
	u64 p_blkno, p_blocks;
	int virtual, blocks, status, i, bytes_left;

	bytes_left = i_size_read(inode) + 1;
	/* we can't trust i_blocks because we're actually going to
	 * write i_size + 1 bytes. */
	blocks = (bytes_left + sb->s_blocksize - 1) >> sb->s_blocksize_bits;

	mlog_entry("i_blocks = %llu, i_size = %llu, blocks = %d\n",
			(unsigned long long)inode->i_blocks,
			i_size_read(inode), blocks);

	/* Sanity check -- make sure we're going to fit. */
	if (bytes_left >
	    ocfs2_clusters_to_bytes(sb, OCFS2_I(inode)->ip_clusters)) {
		status = -EIO;
		mlog_errno(status);
		goto bail;
	}

	bhs = kcalloc(blocks, sizeof(struct buffer_head *), GFP_KERNEL);
	if (!bhs) {
		status = -ENOMEM;
		mlog_errno(status);
		goto bail;
	}

	status = ocfs2_extent_map_get_blocks(inode, 0, &p_blkno, &p_blocks,
					     NULL);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	/* links can never be larger than one cluster so we know this
	 * is all going to be contiguous, but do a sanity check
	 * anyway. */
	if ((p_blocks << sb->s_blocksize_bits) < bytes_left) {
		status = -EIO;
		mlog_errno(status);
		goto bail;
	}

	virtual = 0;
	while(bytes_left > 0) {
		c = &symname[virtual * sb->s_blocksize];

		bhs[virtual] = sb_getblk(sb, p_blkno);
		if (!bhs[virtual]) {
			status = -ENOMEM;
			mlog_errno(status);
			goto bail;
		}
		ocfs2_set_new_buffer_uptodate(INODE_CACHE(inode),
					      bhs[virtual]);

		status = ocfs2_journal_access(handle, INODE_CACHE(inode),
					      bhs[virtual],
					      OCFS2_JOURNAL_ACCESS_CREATE);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}

		memset(bhs[virtual]->b_data, 0, sb->s_blocksize);

		memcpy(bhs[virtual]->b_data, c,
		       (bytes_left > sb->s_blocksize) ? sb->s_blocksize :
		       bytes_left);

		status = ocfs2_journal_dirty(handle, bhs[virtual]);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}

		virtual++;
		p_blkno++;
		bytes_left -= sb->s_blocksize;
	}

	status = 0;
bail:

	if (bhs) {
		for(i = 0; i < blocks; i++)
			brelse(bhs[i]);
		kfree(bhs);
	}

	mlog_exit(status);
	return status;
}