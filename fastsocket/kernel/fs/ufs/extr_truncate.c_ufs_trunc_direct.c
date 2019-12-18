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
struct ufs_sb_private_info {int s_fpbmask; unsigned int s_fpb; } ;
struct ufs_inode_info {int /*<<< orphan*/  i_lastfrag; } ;
struct super_block {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; struct super_block* i_sb; } ;
struct TYPE_2__ {struct ufs_sb_private_info* s_uspi; } ;

/* Variables and functions */
 int DIRECT_FRAGMENT ; 
 int /*<<< orphan*/  UFSD (char*,int /*<<< orphan*/ ,...) ; 
 struct ufs_inode_info* UFS_I (struct inode*) ; 
 int /*<<< orphan*/  UFS_NDIR_FRAGMENT ; 
 TYPE_1__* UFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u32 ; 
 int /*<<< orphan*/  ufs_data_ptr_clear (struct ufs_sb_private_info*,void*) ; 
 unsigned int ufs_data_ptr_to_cpu (struct super_block*,void*) ; 
 int ufs_fragnum (int) ; 
 unsigned int ufs_fragstoblks (int) ; 
 int /*<<< orphan*/  ufs_free_blocks (struct inode*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ufs_free_fragments (struct inode*,unsigned int,int) ; 
 void* ufs_get_direct_data_ptr (struct ufs_sb_private_info*,struct ufs_inode_info*,unsigned int) ; 
 int /*<<< orphan*/  ufs_panic (struct super_block*,char*,char*) ; 

__attribute__((used)) static int ufs_trunc_direct(struct inode *inode)
{
	struct ufs_inode_info *ufsi = UFS_I(inode);
	struct super_block * sb;
	struct ufs_sb_private_info * uspi;
	void *p;
	u64 frag1, frag2, frag3, frag4, block1, block2;
	unsigned frag_to_free, free_count;
	unsigned i, tmp;
	int retry;
	
	UFSD("ENTER: ino %lu\n", inode->i_ino);

	sb = inode->i_sb;
	uspi = UFS_SB(sb)->s_uspi;
	
	frag_to_free = 0;
	free_count = 0;
	retry = 0;
	
	frag1 = DIRECT_FRAGMENT;
	frag4 = min_t(u32, UFS_NDIR_FRAGMENT, ufsi->i_lastfrag);
	frag2 = ((frag1 & uspi->s_fpbmask) ? ((frag1 | uspi->s_fpbmask) + 1) : frag1);
	frag3 = frag4 & ~uspi->s_fpbmask;
	block1 = block2 = 0;
	if (frag2 > frag3) {
		frag2 = frag4;
		frag3 = frag4 = 0;
	} else if (frag2 < frag3) {
		block1 = ufs_fragstoblks (frag2);
		block2 = ufs_fragstoblks (frag3);
	}

	UFSD("ino %lu, frag1 %llu, frag2 %llu, block1 %llu, block2 %llu,"
	     " frag3 %llu, frag4 %llu\n", inode->i_ino,
	     (unsigned long long)frag1, (unsigned long long)frag2,
	     (unsigned long long)block1, (unsigned long long)block2,
	     (unsigned long long)frag3, (unsigned long long)frag4);

	if (frag1 >= frag2)
		goto next1;		

	/*
	 * Free first free fragments
	 */
	p = ufs_get_direct_data_ptr(uspi, ufsi, ufs_fragstoblks(frag1));
	tmp = ufs_data_ptr_to_cpu(sb, p);
	if (!tmp )
		ufs_panic (sb, "ufs_trunc_direct", "internal error");
	frag2 -= frag1;
	frag1 = ufs_fragnum (frag1);

	ufs_free_fragments(inode, tmp + frag1, frag2);
	mark_inode_dirty(inode);
	frag_to_free = tmp + frag1;

next1:
	/*
	 * Free whole blocks
	 */
	for (i = block1 ; i < block2; i++) {
		p = ufs_get_direct_data_ptr(uspi, ufsi, i);
		tmp = ufs_data_ptr_to_cpu(sb, p);
		if (!tmp)
			continue;
		ufs_data_ptr_clear(uspi, p);

		if (free_count == 0) {
			frag_to_free = tmp;
			free_count = uspi->s_fpb;
		} else if (free_count > 0 && frag_to_free == tmp - free_count)
			free_count += uspi->s_fpb;
		else {
			ufs_free_blocks (inode, frag_to_free, free_count);
			frag_to_free = tmp;
			free_count = uspi->s_fpb;
		}
		mark_inode_dirty(inode);
	}
	
	if (free_count > 0)
		ufs_free_blocks (inode, frag_to_free, free_count);

	if (frag3 >= frag4)
		goto next3;

	/*
	 * Free last free fragments
	 */
	p = ufs_get_direct_data_ptr(uspi, ufsi, ufs_fragstoblks(frag3));
	tmp = ufs_data_ptr_to_cpu(sb, p);
	if (!tmp )
		ufs_panic(sb, "ufs_truncate_direct", "internal error");
	frag4 = ufs_fragnum (frag4);
	ufs_data_ptr_clear(uspi, p);

	ufs_free_fragments (inode, tmp, frag4);
	mark_inode_dirty(inode);
 next3:

	UFSD("EXIT: ino %lu\n", inode->i_ino);
	return retry;
}