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
struct dcssblk_dev_info {unsigned long end; unsigned long start; } ;
struct block_device {TYPE_1__* bd_disk; } ;
typedef  int sector_t ;
struct TYPE_2__ {struct dcssblk_dev_info* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ERANGE ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 unsigned long virt_to_phys (void*) ; 

__attribute__((used)) static int
dcssblk_direct_access (struct block_device *bdev, sector_t secnum,
			void **kaddr, unsigned long *pfn)
{
	struct dcssblk_dev_info *dev_info;
	unsigned long pgoff;

	dev_info = bdev->bd_disk->private_data;
	if (!dev_info)
		return -ENODEV;
	if (secnum % (PAGE_SIZE/512))
		return -EINVAL;
	pgoff = secnum / (PAGE_SIZE / 512);
	if ((pgoff+1)*PAGE_SIZE-1 > dev_info->end - dev_info->start)
		return -ERANGE;
	*kaddr = (void *) (dev_info->start+pgoff*PAGE_SIZE);
	*pfn = virt_to_phys(*kaddr) >> PAGE_SHIFT;

	return 0;
}