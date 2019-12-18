#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct ufs_sb_private_info {int s_fpbshift; int s_apbshift; int s_sbbase; int s_fpbmask; scalar_t__ s_apbmask; } ;
struct TYPE_3__ {long* u2_i_data; int /*<<< orphan*/ * i_data; } ;
struct ufs_inode_info {TYPE_1__ i_u1; } ;
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int sector_t ;
typedef  long __fs64 ;
typedef  int /*<<< orphan*/  __fs32 ;
struct TYPE_4__ {unsigned int s_flags; struct ufs_sb_private_info* s_uspi; } ;

/* Variables and functions */
 int /*<<< orphan*/  UFSD (char*,int,int,...) ; 
 struct ufs_inode_info* UFS_I (struct inode*) ; 
 TYPE_2__* UFS_SB (struct super_block*) ; 
 unsigned int UFS_TYPE_MASK ; 
 unsigned int UFS_TYPE_UFS2 ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int fs32_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 
 int fs64_to_cpu (struct super_block*,long) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 struct buffer_head* sb_bread (struct super_block*,int) ; 
 int ufs_block_to_path (struct inode*,int,int*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static u64 ufs_frag_map(struct inode *inode, sector_t frag)
{
	struct ufs_inode_info *ufsi = UFS_I(inode);
	struct super_block *sb = inode->i_sb;
	struct ufs_sb_private_info *uspi = UFS_SB(sb)->s_uspi;
	u64 mask = (u64) uspi->s_apbmask>>uspi->s_fpbshift;
	int shift = uspi->s_apbshift-uspi->s_fpbshift;
	sector_t offsets[4], *p;
	int depth = ufs_block_to_path(inode, frag >> uspi->s_fpbshift, offsets);
	u64  ret = 0L;
	__fs32 block;
	__fs64 u2_block = 0L;
	unsigned flags = UFS_SB(sb)->s_flags;
	u64 temp = 0L;

	UFSD(": frag = %llu  depth = %d\n", (unsigned long long)frag, depth);
	UFSD(": uspi->s_fpbshift = %d ,uspi->s_apbmask = %x, mask=%llx\n",
		uspi->s_fpbshift, uspi->s_apbmask,
		(unsigned long long)mask);

	if (depth == 0)
		return 0;

	p = offsets;

	lock_kernel();
	if ((flags & UFS_TYPE_MASK) == UFS_TYPE_UFS2)
		goto ufs2;

	block = ufsi->i_u1.i_data[*p++];
	if (!block)
		goto out;
	while (--depth) {
		struct buffer_head *bh;
		sector_t n = *p++;

		bh = sb_bread(sb, uspi->s_sbbase + fs32_to_cpu(sb, block)+(n>>shift));
		if (!bh)
			goto out;
		block = ((__fs32 *) bh->b_data)[n & mask];
		brelse (bh);
		if (!block)
			goto out;
	}
	ret = (u64) (uspi->s_sbbase + fs32_to_cpu(sb, block) + (frag & uspi->s_fpbmask));
	goto out;
ufs2:
	u2_block = ufsi->i_u1.u2_i_data[*p++];
	if (!u2_block)
		goto out;


	while (--depth) {
		struct buffer_head *bh;
		sector_t n = *p++;


		temp = (u64)(uspi->s_sbbase) + fs64_to_cpu(sb, u2_block);
		bh = sb_bread(sb, temp +(u64) (n>>shift));
		if (!bh)
			goto out;
		u2_block = ((__fs64 *)bh->b_data)[n & mask];
		brelse(bh);
		if (!u2_block)
			goto out;
	}
	temp = (u64)uspi->s_sbbase + fs64_to_cpu(sb, u2_block);
	ret = temp + (u64) (frag & uspi->s_fpbmask);

out:
	unlock_kernel();
	return ret;
}