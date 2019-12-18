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
struct nilfs_dat_entry {int /*<<< orphan*/  de_blocknr; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_page; } ;
typedef  scalar_t__ sector_t ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  KM_USER0 ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* kmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct nilfs_dat_entry* nilfs_palloc_block_get_entry (struct inode*,int /*<<< orphan*/ ,struct buffer_head*,void*) ; 
 int nilfs_palloc_get_entry_block (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 

int nilfs_dat_translate(struct inode *dat, __u64 vblocknr, sector_t *blocknrp)
{
	struct buffer_head *entry_bh;
	struct nilfs_dat_entry *entry;
	sector_t blocknr;
	void *kaddr;
	int ret;

	ret = nilfs_palloc_get_entry_block(dat, vblocknr, 0, &entry_bh);
	if (ret < 0)
		return ret;

	kaddr = kmap_atomic(entry_bh->b_page, KM_USER0);
	entry = nilfs_palloc_block_get_entry(dat, vblocknr, entry_bh, kaddr);
	blocknr = le64_to_cpu(entry->de_blocknr);
	if (blocknr == 0) {
		ret = -ENOENT;
		goto out;
	}
	if (blocknrp != NULL)
		*blocknrp = blocknr;

 out:
	kunmap_atomic(kaddr, KM_USER0);
	brelse(entry_bh);
	return ret;
}