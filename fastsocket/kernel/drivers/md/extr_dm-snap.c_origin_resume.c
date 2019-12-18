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
struct dm_target {int /*<<< orphan*/  split_io; struct dm_dev* private; } ;
struct dm_dev {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_origin_minimum_chunksize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void origin_resume(struct dm_target *ti)
{
	struct dm_dev *dev = ti->private;

	ti->split_io = get_origin_minimum_chunksize(dev->bdev);
}