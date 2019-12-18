#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct md_rdev {unsigned long long sb_start; TYPE_2__* mddev; int /*<<< orphan*/  sb_page; int /*<<< orphan*/  sb_size; } ;
typedef  unsigned long long sector_t ;
struct TYPE_4__ {scalar_t__ offset; } ;
struct TYPE_5__ {unsigned long long dev_sectors; int level; TYPE_1__ bitmap_info; } ;

/* Variables and functions */
 unsigned long long calc_dev_sboffset (struct md_rdev*) ; 
 int /*<<< orphan*/  md_super_wait (TYPE_2__*) ; 
 int /*<<< orphan*/  md_super_write (TYPE_2__*,struct md_rdev*,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long long
super_90_rdev_size_change(struct md_rdev *rdev, sector_t num_sectors)
{
	if (num_sectors && num_sectors < rdev->mddev->dev_sectors)
		return 0; /* component must fit device */
	if (rdev->mddev->bitmap_info.offset)
		return 0; /* can't move bitmap */
	rdev->sb_start = calc_dev_sboffset(rdev);
	if (!num_sectors || num_sectors > rdev->sb_start)
		num_sectors = rdev->sb_start;
	/* Limit to 4TB as metadata cannot record more than that.
	 * 4TB == 2^32 KB, or 2*2^32 sectors.
	 */
	if (num_sectors >= (2ULL << 32) && rdev->mddev->level >= 1)
		num_sectors = (2ULL << 32) - 2;
	md_super_write(rdev->mddev, rdev, rdev->sb_start, rdev->sb_size,
		       rdev->sb_page);
	md_super_wait(rdev->mddev);
	return num_sectors;
}