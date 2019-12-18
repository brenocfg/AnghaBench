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
struct nilfs_bmap {int /*<<< orphan*/  b_sem; TYPE_1__* b_ops; } ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_2__ {int (* bop_lookup_contig ) (struct nilfs_bmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int stub1 (struct nilfs_bmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int nilfs_bmap_lookup_contig(struct nilfs_bmap *bmap, __u64 key, __u64 *ptrp,
			     unsigned maxblocks)
{
	int ret;

	down_read(&bmap->b_sem);
	ret = bmap->b_ops->bop_lookup_contig(bmap, key, ptrp, maxblocks);
	up_read(&bmap->b_sem);
	return ret;
}