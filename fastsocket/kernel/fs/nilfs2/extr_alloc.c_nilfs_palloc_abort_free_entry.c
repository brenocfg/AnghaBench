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
struct nilfs_palloc_req {int /*<<< orphan*/ * pr_desc_bh; int /*<<< orphan*/ * pr_bitmap_bh; scalar_t__ pr_entry_nr; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 

void nilfs_palloc_abort_free_entry(struct inode *inode,
				   struct nilfs_palloc_req *req)
{
	brelse(req->pr_bitmap_bh);
	brelse(req->pr_desc_bh);

	req->pr_entry_nr = 0;
	req->pr_bitmap_bh = NULL;
	req->pr_desc_bh = NULL;
}