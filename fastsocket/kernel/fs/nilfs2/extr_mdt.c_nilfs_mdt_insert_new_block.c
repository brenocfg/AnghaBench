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
struct nilfs_inode_info {int /*<<< orphan*/  i_bmap; } ;
struct inode {int i_blkbits; } ;
struct buffer_head {int /*<<< orphan*/  b_page; scalar_t__ b_blocknr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_USER0 ; 
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 int bh_offset (struct buffer_head*) ; 
 int /*<<< orphan*/  flush_dcache_page (int /*<<< orphan*/ ) ; 
 void* kmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int nilfs_bmap_insert (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  nilfs_mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_dirty (struct inode*) ; 
 int /*<<< orphan*/  set_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
nilfs_mdt_insert_new_block(struct inode *inode, unsigned long block,
			   struct buffer_head *bh,
			   void (*init_block)(struct inode *,
					      struct buffer_head *, void *))
{
	struct nilfs_inode_info *ii = NILFS_I(inode);
	void *kaddr;
	int ret;

	/* Caller exclude read accesses using page lock */

	/* set_buffer_new(bh); */
	bh->b_blocknr = 0;

	ret = nilfs_bmap_insert(ii->i_bmap, block, (unsigned long)bh);
	if (unlikely(ret))
		return ret;

	set_buffer_mapped(bh);

	kaddr = kmap_atomic(bh->b_page, KM_USER0);
	memset(kaddr + bh_offset(bh), 0, 1 << inode->i_blkbits);
	if (init_block)
		init_block(inode, bh, kaddr);
	flush_dcache_page(bh->b_page);
	kunmap_atomic(kaddr, KM_USER0);

	set_buffer_uptodate(bh);
	nilfs_mark_buffer_dirty(bh);
	nilfs_mdt_mark_dirty(inode);
	return 0;
}