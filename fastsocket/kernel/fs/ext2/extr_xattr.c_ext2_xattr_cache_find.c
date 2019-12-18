#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mb_cache_entry {scalar_t__ e_block; } ;
struct inode {TYPE_1__* i_sb; int /*<<< orphan*/  i_ino; } ;
struct ext2_xattr_header {int /*<<< orphan*/  h_hash; } ;
struct buffer_head {int /*<<< orphan*/  b_count; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_6__ {int /*<<< orphan*/  h_refcount; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 scalar_t__ EXT2_XATTR_REFCOUNT_MAX ; 
 TYPE_2__* HDR (struct buffer_head*) ; 
 scalar_t__ IS_ERR (struct mb_cache_entry*) ; 
 int /*<<< orphan*/  PTR_ERR (struct mb_cache_entry*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  ea_bdebug (struct buffer_head*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ea_idebug (struct inode*,char*,unsigned long,...) ; 
 int /*<<< orphan*/  ext2_error (TYPE_1__*,char*,char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ext2_xattr_cache ; 
 int /*<<< orphan*/  ext2_xattr_cmp (struct ext2_xattr_header*,TYPE_2__*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 struct mb_cache_entry* mb_cache_entry_find_first (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct mb_cache_entry* mb_cache_entry_find_next (struct mb_cache_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mb_cache_entry_release (struct mb_cache_entry*) ; 
 struct buffer_head* sb_bread (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static struct buffer_head *
ext2_xattr_cache_find(struct inode *inode, struct ext2_xattr_header *header)
{
	__u32 hash = le32_to_cpu(header->h_hash);
	struct mb_cache_entry *ce;

	if (!header->h_hash)
		return NULL;  /* never share */
	ea_idebug(inode, "looking for cached blocks [%x]", (int)hash);
again:
	ce = mb_cache_entry_find_first(ext2_xattr_cache, 0,
				       inode->i_sb->s_bdev, hash);
	while (ce) {
		struct buffer_head *bh;

		if (IS_ERR(ce)) {
			if (PTR_ERR(ce) == -EAGAIN)
				goto again;
			break;
		}

		bh = sb_bread(inode->i_sb, ce->e_block);
		if (!bh) {
			ext2_error(inode->i_sb, "ext2_xattr_cache_find",
				"inode %ld: block %ld read error",
				inode->i_ino, (unsigned long) ce->e_block);
		} else {
			lock_buffer(bh);
			if (le32_to_cpu(HDR(bh)->h_refcount) >
				   EXT2_XATTR_REFCOUNT_MAX) {
				ea_idebug(inode, "block %ld refcount %d>%d",
					  (unsigned long) ce->e_block,
					  le32_to_cpu(HDR(bh)->h_refcount),
					  EXT2_XATTR_REFCOUNT_MAX);
			} else if (!ext2_xattr_cmp(header, HDR(bh))) {
				ea_bdebug(bh, "b_count=%d",
					  atomic_read(&(bh->b_count)));
				mb_cache_entry_release(ce);
				return bh;
			}
			unlock_buffer(bh);
			brelse(bh);
		}
		ce = mb_cache_entry_find_next(ce, 0, inode->i_sb->s_bdev, hash);
	}
	return NULL;
}