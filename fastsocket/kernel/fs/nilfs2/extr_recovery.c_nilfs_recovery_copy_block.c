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
struct page {int dummy; } ;
struct nilfs_sb_info {int /*<<< orphan*/  s_super; } ;
struct nilfs_recovery_block {int /*<<< orphan*/  blocknr; } ;
struct buffer_head {int /*<<< orphan*/  b_size; int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  KM_USER0 ; 
 int bh_offset (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nilfs_recovery_copy_block(struct nilfs_sb_info *sbi,
				     struct nilfs_recovery_block *rb,
				     struct page *page)
{
	struct buffer_head *bh_org;
	void *kaddr;

	bh_org = sb_bread(sbi->s_super, rb->blocknr);
	if (unlikely(!bh_org))
		return -EIO;

	kaddr = kmap_atomic(page, KM_USER0);
	memcpy(kaddr + bh_offset(bh_org), bh_org->b_data, bh_org->b_size);
	kunmap_atomic(kaddr, KM_USER0);
	brelse(bh_org);
	return 0;
}