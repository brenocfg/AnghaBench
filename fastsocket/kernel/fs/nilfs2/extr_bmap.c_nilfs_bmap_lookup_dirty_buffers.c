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
struct nilfs_bmap {TYPE_1__* b_ops; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* bop_lookup_dirty_buffers ) (struct nilfs_bmap*,struct list_head*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nilfs_bmap*,struct list_head*) ; 

void nilfs_bmap_lookup_dirty_buffers(struct nilfs_bmap *bmap,
				     struct list_head *listp)
{
	if (bmap->b_ops->bop_lookup_dirty_buffers != NULL)
		bmap->b_ops->bop_lookup_dirty_buffers(bmap, listp);
}