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
struct nilfs_palloc_req {int /*<<< orphan*/  pr_entry_nr; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  nilfs_dat_commit_entry (struct inode*,struct nilfs_palloc_req*) ; 
 int nilfs_dat_prepare_entry (struct inode*,struct nilfs_palloc_req*,int /*<<< orphan*/ ) ; 

int nilfs_dat_mark_dirty(struct inode *dat, __u64 vblocknr)
{
	struct nilfs_palloc_req req;
	int ret;

	req.pr_entry_nr = vblocknr;
	ret = nilfs_dat_prepare_entry(dat, &req, 0);
	if (ret == 0)
		nilfs_dat_commit_entry(dat, &req);
	return ret;
}