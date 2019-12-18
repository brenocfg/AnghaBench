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
struct md_rdev {int /*<<< orphan*/  badblocks; scalar_t__ data_offset; scalar_t__ new_data_offset; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int md_clear_badblocks (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int rdev_clear_badblocks(struct md_rdev *rdev, sector_t s, int sectors,
			 int is_new)
{
	if (is_new)
		s += rdev->new_data_offset;
	else
		s += rdev->data_offset;
	return md_clear_badblocks(&rdev->badblocks,
				  s, sectors);
}