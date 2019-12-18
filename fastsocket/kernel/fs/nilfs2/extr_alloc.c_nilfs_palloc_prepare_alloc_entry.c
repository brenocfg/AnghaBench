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
struct nilfs_palloc_req {unsigned long pr_entry_nr; struct buffer_head* pr_bitmap_bh; struct buffer_head* pr_desc_bh; } ;
struct nilfs_palloc_group_desc {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_page; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 unsigned char* nilfs_palloc_block_get_bitmap (struct inode*,struct buffer_head*,void*) ; 
 struct nilfs_palloc_group_desc* nilfs_palloc_block_get_group_desc (struct inode*,unsigned long,struct buffer_head*,void*) ; 
 unsigned long nilfs_palloc_entries_per_group (struct inode*) ; 
 int nilfs_palloc_find_available_slot (struct inode*,unsigned long,unsigned long,unsigned char*,unsigned long) ; 
 int nilfs_palloc_get_bitmap_block (struct inode*,unsigned long,int,struct buffer_head**) ; 
 int nilfs_palloc_get_desc_block (struct inode*,unsigned long,int,struct buffer_head**) ; 
 int nilfs_palloc_group (struct inode*,unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  nilfs_palloc_group_desc_add_entries (struct inode*,unsigned long,struct nilfs_palloc_group_desc*,int) ; 
 scalar_t__ nilfs_palloc_group_desc_nfrees (struct inode*,unsigned long,struct nilfs_palloc_group_desc*) ; 
 unsigned long nilfs_palloc_groups_count (struct inode*) ; 
 unsigned long nilfs_palloc_groups_per_desc_block (struct inode*) ; 
 unsigned long nilfs_palloc_rest_groups_in_desc_block (struct inode*,unsigned long,unsigned long) ; 

int nilfs_palloc_prepare_alloc_entry(struct inode *inode,
				     struct nilfs_palloc_req *req)
{
	struct buffer_head *desc_bh, *bitmap_bh;
	struct nilfs_palloc_group_desc *desc;
	unsigned char *bitmap;
	void *desc_kaddr, *bitmap_kaddr;
	unsigned long group, maxgroup, ngroups;
	unsigned long group_offset, maxgroup_offset;
	unsigned long n, entries_per_group, groups_per_desc_block;
	unsigned long i, j;
	int pos, ret;

	ngroups = nilfs_palloc_groups_count(inode);
	maxgroup = ngroups - 1;
	group = nilfs_palloc_group(inode, req->pr_entry_nr, &group_offset);
	entries_per_group = nilfs_palloc_entries_per_group(inode);
	groups_per_desc_block = nilfs_palloc_groups_per_desc_block(inode);

	for (i = 0; i < ngroups; i += n) {
		if (group >= ngroups) {
			/* wrap around */
			group = 0;
			maxgroup = nilfs_palloc_group(inode, req->pr_entry_nr,
						      &maxgroup_offset) - 1;
		}
		ret = nilfs_palloc_get_desc_block(inode, group, 1, &desc_bh);
		if (ret < 0)
			return ret;
		desc_kaddr = kmap(desc_bh->b_page);
		desc = nilfs_palloc_block_get_group_desc(
			inode, group, desc_bh, desc_kaddr);
		n = nilfs_palloc_rest_groups_in_desc_block(inode, group,
							   maxgroup);
		for (j = 0; j < n; j++, desc++, group++) {
			if (nilfs_palloc_group_desc_nfrees(inode, group, desc)
			    > 0) {
				ret = nilfs_palloc_get_bitmap_block(
					inode, group, 1, &bitmap_bh);
				if (ret < 0)
					goto out_desc;
				bitmap_kaddr = kmap(bitmap_bh->b_page);
				bitmap = nilfs_palloc_block_get_bitmap(
					inode, bitmap_bh, bitmap_kaddr);
				pos = nilfs_palloc_find_available_slot(
					inode, group, group_offset, bitmap,
					entries_per_group);
				if (pos >= 0) {
					/* found a free entry */
					nilfs_palloc_group_desc_add_entries(
						inode, group, desc, -1);
					req->pr_entry_nr =
						entries_per_group * group + pos;
					kunmap(desc_bh->b_page);
					kunmap(bitmap_bh->b_page);

					req->pr_desc_bh = desc_bh;
					req->pr_bitmap_bh = bitmap_bh;
					return 0;
				}
				kunmap(bitmap_bh->b_page);
				brelse(bitmap_bh);
			}

			group_offset = 0;
		}

		kunmap(desc_bh->b_page);
		brelse(desc_bh);
	}

	/* no entries left */
	return -ENOSPC;

 out_desc:
	kunmap(desc_bh->b_page);
	brelse(desc_bh);
	return ret;
}