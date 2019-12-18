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
struct hd_struct {int dummy; } ;
struct gendisk {int dummy; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 struct block_device* bdget (int /*<<< orphan*/ ) ; 
 struct hd_struct* disk_get_part (struct gendisk*,int) ; 
 int /*<<< orphan*/  disk_put_part (struct hd_struct*) ; 
 int /*<<< orphan*/  part_devt (struct hd_struct*) ; 

struct block_device *bdget_disk(struct gendisk *disk, int partno)
{
	struct hd_struct *part;
	struct block_device *bdev = NULL;

	part = disk_get_part(disk, partno);
	if (part)
		bdev = bdget(part_devt(part));
	disk_put_part(part);

	return bdev;
}