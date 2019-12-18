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
typedef  unsigned long __u64 ;
struct TYPE_2__ {int (* bop_last_key ) (struct nilfs_bmap*,unsigned long*) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int nilfs_bmap_do_delete (struct nilfs_bmap*,unsigned long) ; 
 int stub1 (struct nilfs_bmap*,unsigned long*) ; 
 int stub2 (struct nilfs_bmap*,unsigned long*) ; 

__attribute__((used)) static int nilfs_bmap_do_truncate(struct nilfs_bmap *bmap, unsigned long key)
{
	__u64 lastkey;
	int ret;

	ret = bmap->b_ops->bop_last_key(bmap, &lastkey);
	if (ret < 0) {
		if (ret == -ENOENT)
			ret = 0;
		return ret;
	}

	while (key <= lastkey) {
		ret = nilfs_bmap_do_delete(bmap, lastkey);
		if (ret < 0)
			return ret;
		ret = bmap->b_ops->bop_last_key(bmap, &lastkey);
		if (ret < 0) {
			if (ret == -ENOENT)
				ret = 0;
			return ret;
		}
	}
	return 0;
}