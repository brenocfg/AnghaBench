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
struct block_device {TYPE_1__* bd_part; int /*<<< orphan*/  bd_disk; } ;
struct TYPE_2__ {int /*<<< orphan*/  partno; } ;

/* Variables and functions */
 char const* disk_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

const char *bdevname(struct block_device *bdev, char *buf)
{
	return disk_name(bdev->bd_disk, bdev->bd_part->partno, buf);
}