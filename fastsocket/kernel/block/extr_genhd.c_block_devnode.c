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
struct gendisk {char* (* devnode ) (struct gendisk*,int /*<<< orphan*/ *) ;} ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 struct gendisk* dev_to_disk (struct device*) ; 
 char* stub1 (struct gendisk*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *block_devnode(struct device *dev, mode_t *mode)
{
	struct gendisk *disk = dev_to_disk(dev);

	if (disk->devnode)
		return disk->devnode(disk, mode);
	return NULL;
}