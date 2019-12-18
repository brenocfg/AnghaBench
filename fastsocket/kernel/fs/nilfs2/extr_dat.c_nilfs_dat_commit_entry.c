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
struct nilfs_palloc_req {int /*<<< orphan*/  pr_entry_bh; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_buffer_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_dirty (struct inode*) ; 

__attribute__((used)) static void nilfs_dat_commit_entry(struct inode *dat,
				   struct nilfs_palloc_req *req)
{
	nilfs_mdt_mark_buffer_dirty(req->pr_entry_bh);
	nilfs_mdt_mark_dirty(dat);
	brelse(req->pr_entry_bh);
}