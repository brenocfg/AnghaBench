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
struct nilfs_palloc_req {TYPE_1__* pr_entry_bh; int /*<<< orphan*/  pr_entry_nr; } ;
struct nilfs_dat_entry {int /*<<< orphan*/  de_blocknr; int /*<<< orphan*/  de_start; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ sector_t ;
typedef  void* __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  b_page; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  KM_USER0 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 void* kmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_dat_abort_entry (struct inode*,struct nilfs_palloc_req*) ; 
 int nilfs_dat_prepare_entry (struct inode*,struct nilfs_palloc_req*,int /*<<< orphan*/ ) ; 
 struct nilfs_dat_entry* nilfs_palloc_block_get_entry (struct inode*,int /*<<< orphan*/ ,TYPE_1__*,void*) ; 
 int nilfs_palloc_prepare_free_entry (struct inode*,struct nilfs_palloc_req*) ; 

int nilfs_dat_prepare_end(struct inode *dat, struct nilfs_palloc_req *req)
{
	struct nilfs_dat_entry *entry;
	__u64 start;
	sector_t blocknr;
	void *kaddr;
	int ret;

	ret = nilfs_dat_prepare_entry(dat, req, 0);
	if (ret < 0) {
		WARN_ON(ret == -ENOENT);
		return ret;
	}

	kaddr = kmap_atomic(req->pr_entry_bh->b_page, KM_USER0);
	entry = nilfs_palloc_block_get_entry(dat, req->pr_entry_nr,
					     req->pr_entry_bh, kaddr);
	start = le64_to_cpu(entry->de_start);
	blocknr = le64_to_cpu(entry->de_blocknr);
	kunmap_atomic(kaddr, KM_USER0);

	if (blocknr == 0) {
		ret = nilfs_palloc_prepare_free_entry(dat, req);
		if (ret < 0) {
			nilfs_dat_abort_entry(dat, req);
			return ret;
		}
	}

	return 0;
}