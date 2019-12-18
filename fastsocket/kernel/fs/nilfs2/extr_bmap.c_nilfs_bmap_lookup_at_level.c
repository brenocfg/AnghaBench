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
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_2__ {int (* bop_lookup ) (struct nilfs_bmap*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ NILFS_BMAP_USE_VBN (struct nilfs_bmap*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_bmap_get_dat (struct nilfs_bmap*) ; 
 int nilfs_dat_translate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct nilfs_bmap*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int nilfs_bmap_lookup_at_level(struct nilfs_bmap *bmap, __u64 key, int level,
			       __u64 *ptrp)
{
	sector_t blocknr;
	int ret;

	down_read(&bmap->b_sem);
	ret = bmap->b_ops->bop_lookup(bmap, key, level, ptrp);
	if (ret < 0)
		goto out;
	if (NILFS_BMAP_USE_VBN(bmap)) {
		ret = nilfs_dat_translate(nilfs_bmap_get_dat(bmap), *ptrp,
					  &blocknr);
		if (!ret)
			*ptrp = blocknr;
	}

 out:
	up_read(&bmap->b_sem);
	return ret;
}