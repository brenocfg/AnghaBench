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
struct nilfs_dat_entry {void* de_blocknr; void* de_end; void* de_start; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  b_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_USER0 ; 
 int /*<<< orphan*/  NILFS_CNO_MAX ; 
 int /*<<< orphan*/  NILFS_CNO_MIN ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 void* kmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_dat_commit_entry (struct inode*,struct nilfs_palloc_req*) ; 
 struct nilfs_dat_entry* nilfs_palloc_block_get_entry (struct inode*,int /*<<< orphan*/ ,TYPE_1__*,void*) ; 
 int /*<<< orphan*/  nilfs_palloc_commit_alloc_entry (struct inode*,struct nilfs_palloc_req*) ; 

void nilfs_dat_commit_alloc(struct inode *dat, struct nilfs_palloc_req *req)
{
	struct nilfs_dat_entry *entry;
	void *kaddr;

	kaddr = kmap_atomic(req->pr_entry_bh->b_page, KM_USER0);
	entry = nilfs_palloc_block_get_entry(dat, req->pr_entry_nr,
					     req->pr_entry_bh, kaddr);
	entry->de_start = cpu_to_le64(NILFS_CNO_MIN);
	entry->de_end = cpu_to_le64(NILFS_CNO_MAX);
	entry->de_blocknr = cpu_to_le64(0);
	kunmap_atomic(kaddr, KM_USER0);

	nilfs_palloc_commit_alloc_entry(dat, req);
	nilfs_dat_commit_entry(dat, req);
}