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
typedef  union nilfs_binfo {int dummy; } nilfs_binfo ;
struct nilfs_bmap {int /*<<< orphan*/  b_sem; TYPE_1__* b_ops; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int (* bop_assign ) (struct nilfs_bmap*,struct buffer_head**,unsigned long,union nilfs_binfo*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int stub1 (struct nilfs_bmap*,struct buffer_head**,unsigned long,union nilfs_binfo*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int nilfs_bmap_assign(struct nilfs_bmap *bmap,
		      struct buffer_head **bh,
		      unsigned long blocknr,
		      union nilfs_binfo *binfo)
{
	int ret;

	down_write(&bmap->b_sem);
	ret = bmap->b_ops->bop_assign(bmap, bh, blocknr, binfo);
	up_write(&bmap->b_sem);
	return ret;
}