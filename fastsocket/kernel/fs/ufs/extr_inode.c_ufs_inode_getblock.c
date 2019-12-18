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
struct ufs_sb_private_info {scalar_t__ fs_magic; int s_sbbase; int s_fpb; } ;
struct super_block {int dummy; } ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_ino; struct super_block* i_sb; } ;
struct buffer_head {int b_blocknr; scalar_t__ b_data; } ;
typedef  scalar_t__ sector_t ;
typedef  int /*<<< orphan*/  __fs64 ;
typedef  int /*<<< orphan*/  __fs32 ;
struct TYPE_2__ {struct ufs_sb_private_info* s_uspi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 int /*<<< orphan*/  READ ; 
 scalar_t__ UFS2_MAGIC ; 
 int /*<<< orphan*/  UFSD (char*,...) ; 
 TYPE_1__* UFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int fs32_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 
 int fs64_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int,struct buffer_head**) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 struct buffer_head* sb_getblk (struct super_block*,int) ; 
 int /*<<< orphan*/  sync_dirty_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  ufs_blknum (scalar_t__) ; 
 int ufs_data_ptr_to_cpu (struct super_block*,void*) ; 
 unsigned int ufs_fragnum (int) ; 
 int ufs_fragstoblks (int) ; 
 int ufs_new_fragments (struct inode*,void*,int /*<<< orphan*/ ,int,int,int*,struct page*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

__attribute__((used)) static struct buffer_head *
ufs_inode_getblock(struct inode *inode, struct buffer_head *bh,
		  u64 fragment, sector_t new_fragment, int *err,
		  long *phys, int *new, struct page *locked_page)
{
	struct super_block *sb = inode->i_sb;
	struct ufs_sb_private_info *uspi = UFS_SB(sb)->s_uspi;
	struct buffer_head * result;
	unsigned blockoff;
	u64 tmp, goal, block;
	void *p;

	block = ufs_fragstoblks (fragment);
	blockoff = ufs_fragnum (fragment);

	UFSD("ENTER, ino %lu, fragment %llu, new_fragment %llu, metadata %d\n",
	     inode->i_ino, (unsigned long long)fragment,
	     (unsigned long long)new_fragment, !phys);

	result = NULL;
	if (!bh)
		goto out;
	if (!buffer_uptodate(bh)) {
		ll_rw_block (READ, 1, &bh);
		wait_on_buffer (bh);
		if (!buffer_uptodate(bh))
			goto out;
	}
	if (uspi->fs_magic == UFS2_MAGIC)
		p = (__fs64 *)bh->b_data + block;
	else
		p = (__fs32 *)bh->b_data + block;
repeat:
	tmp = ufs_data_ptr_to_cpu(sb, p);
	if (tmp) {
		if (!phys) {
			result = sb_getblk(sb, uspi->s_sbbase + tmp + blockoff);
			if (tmp == ufs_data_ptr_to_cpu(sb, p))
				goto out;
			brelse (result);
			goto repeat;
		} else {
			*phys = uspi->s_sbbase + tmp + blockoff;
			goto out;
		}
	}

	if (block && (uspi->fs_magic == UFS2_MAGIC ?
		      (tmp = fs64_to_cpu(sb, ((__fs64 *)bh->b_data)[block-1])) :
		      (tmp = fs32_to_cpu(sb, ((__fs32 *)bh->b_data)[block-1]))))
		goal = tmp + uspi->s_fpb;
	else
		goal = bh->b_blocknr + uspi->s_fpb;
	tmp = ufs_new_fragments(inode, p, ufs_blknum(new_fragment), goal,
				uspi->s_fpb, err, locked_page);
	if (!tmp) {
		if (ufs_data_ptr_to_cpu(sb, p))
			goto repeat;
		goto out;
	}		


	if (!phys) {
		result = sb_getblk(sb, uspi->s_sbbase + tmp + blockoff);
	} else {
		*phys = uspi->s_sbbase + tmp + blockoff;
		*new = 1;
	}

	mark_buffer_dirty(bh);
	if (IS_SYNC(inode))
		sync_dirty_buffer(bh);
	inode->i_ctime = CURRENT_TIME_SEC;
	mark_inode_dirty(inode);
	UFSD("result %llu\n", (unsigned long long)tmp + blockoff);
out:
	brelse (bh);
	UFSD("EXIT\n");
	return result;
}