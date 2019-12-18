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
struct nilfs_dat_entry {void* de_blocknr; void* de_start; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  b_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_USER0 ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 void* kmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_dat_commit_entry (struct inode*,struct nilfs_palloc_req*) ; 
 int /*<<< orphan*/  nilfs_mdt_cno (struct inode*) ; 
 struct nilfs_dat_entry* nilfs_palloc_block_get_entry (struct inode*,int /*<<< orphan*/ ,TYPE_1__*,void*) ; 

void nilfs_dat_commit_start(struct inode *dat, struct nilfs_palloc_req *req,
			    sector_t blocknr)
{
	struct nilfs_dat_entry *entry;
	void *kaddr;

	kaddr = kmap_atomic(req->pr_entry_bh->b_page, KM_USER0);
	entry = nilfs_palloc_block_get_entry(dat, req->pr_entry_nr,
					     req->pr_entry_bh, kaddr);
	entry->de_start = cpu_to_le64(nilfs_mdt_cno(dat));
	entry->de_blocknr = cpu_to_le64(blocknr);
	kunmap_atomic(kaddr, KM_USER0);

	nilfs_dat_commit_entry(dat, req);
}