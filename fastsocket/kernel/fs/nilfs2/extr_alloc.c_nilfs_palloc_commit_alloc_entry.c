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
struct nilfs_palloc_req {int /*<<< orphan*/  pr_desc_bh; int /*<<< orphan*/  pr_bitmap_bh; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_buffer_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_dirty (struct inode*) ; 

void nilfs_palloc_commit_alloc_entry(struct inode *inode,
				     struct nilfs_palloc_req *req)
{
	nilfs_mdt_mark_buffer_dirty(req->pr_bitmap_bh);
	nilfs_mdt_mark_buffer_dirty(req->pr_desc_bh);
	nilfs_mdt_mark_dirty(inode);

	brelse(req->pr_bitmap_bh);
	brelse(req->pr_desc_bh);
}