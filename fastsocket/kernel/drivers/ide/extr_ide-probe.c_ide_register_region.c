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
struct gendisk {int /*<<< orphan*/  minors; int /*<<< orphan*/  first_minor; int /*<<< orphan*/  major; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_register_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gendisk*) ; 
 int /*<<< orphan*/  exact_lock ; 
 int /*<<< orphan*/  exact_match ; 

void ide_register_region(struct gendisk *disk)
{
	blk_register_region(MKDEV(disk->major, disk->first_minor),
			    disk->minors, NULL, exact_match, exact_lock, disk);
}