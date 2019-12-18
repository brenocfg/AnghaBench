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
struct nfs_commit_info {TYPE_1__* ds; } ;
struct TYPE_2__ {int nbuckets; int /*<<< orphan*/ * buckets; } ;

/* Variables and functions */
 int filelayout_scan_ds_commit_list (int /*<<< orphan*/ *,struct nfs_commit_info*,int) ; 

__attribute__((used)) static int filelayout_scan_commit_lists(struct nfs_commit_info *cinfo,
					int max)
{
	int i, rv = 0, cnt;

	for (i = 0; i < cinfo->ds->nbuckets && max != 0; i++) {
		cnt = filelayout_scan_ds_commit_list(&cinfo->ds->buckets[i],
						     cinfo, max);
		max -= cnt;
		rv += cnt;
	}
	return rv;
}