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

/* Variables and functions */
 int /*<<< orphan*/  FMODE_WRITE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int blkdev_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkdev_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resume_bdev ; 
 int root_swap ; 
 int set_blocksize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int swap_type_of (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swsusp_resume_block ; 
 int /*<<< orphan*/  swsusp_resume_device ; 

__attribute__((used)) static int swsusp_swap_check(void) /* This is called before saving image */
{
	int res;

	res = swap_type_of(swsusp_resume_device, swsusp_resume_block,
			&resume_bdev);
	if (res < 0)
		return res;

	root_swap = res;
	res = blkdev_get(resume_bdev, FMODE_WRITE);
	if (res)
		return res;

	res = set_blocksize(resume_bdev, PAGE_SIZE);
	if (res < 0)
		blkdev_put(resume_bdev, FMODE_WRITE);

	return res;
}