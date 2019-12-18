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
struct list_head {int dummy; } ;
struct pnfs_commit_bucket {int /*<<< orphan*/ * clseg; int /*<<< orphan*/ * wlseg; struct list_head committing; struct list_head written; } ;
struct nfs_commit_info {TYPE_1__* ds; } ;
struct TYPE_2__ {int nwritten; int ncommitting; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_lseg (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (struct list_head*) ; 
 int transfer_commit_list (struct list_head*,struct list_head*,struct nfs_commit_info*,int) ; 

__attribute__((used)) static int
filelayout_scan_ds_commit_list(struct pnfs_commit_bucket *bucket,
			       struct nfs_commit_info *cinfo,
			       int max)
{
	struct list_head *src = &bucket->written;
	struct list_head *dst = &bucket->committing;
	int ret;

	ret = transfer_commit_list(src, dst, cinfo, max);
	if (ret) {
		cinfo->ds->nwritten -= ret;
		cinfo->ds->ncommitting += ret;
		bucket->clseg = bucket->wlseg;
		if (list_empty(src))
			bucket->wlseg = NULL;
		else
			get_lseg(bucket->clseg);
	}
	return ret;
}