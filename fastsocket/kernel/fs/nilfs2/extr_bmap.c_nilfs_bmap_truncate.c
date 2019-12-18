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
struct nilfs_bmap {int /*<<< orphan*/  b_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int nilfs_bmap_do_truncate (struct nilfs_bmap*,unsigned long) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int nilfs_bmap_truncate(struct nilfs_bmap *bmap, unsigned long key)
{
	int ret;

	down_write(&bmap->b_sem);
	ret = nilfs_bmap_do_truncate(bmap, key);
	up_write(&bmap->b_sem);
	return ret;
}