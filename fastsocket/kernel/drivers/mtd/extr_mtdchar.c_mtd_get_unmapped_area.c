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
struct mtd_info {unsigned long (* get_unmapped_area ) (struct mtd_info*,unsigned long,unsigned long,unsigned long) ;unsigned long size; } ;
struct mtd_file_info {struct mtd_info* mtd; } ;
struct file {struct mtd_file_info* private_data; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ENOSYS ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long stub1 (struct mtd_info*,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long mtd_get_unmapped_area(struct file *file,
					   unsigned long addr,
					   unsigned long len,
					   unsigned long pgoff,
					   unsigned long flags)
{
	struct mtd_file_info *mfi = file->private_data;
	struct mtd_info *mtd = mfi->mtd;

	if (mtd->get_unmapped_area) {
		unsigned long offset;

		if (addr != 0)
			return (unsigned long) -EINVAL;

		if (len > mtd->size || pgoff >= (mtd->size >> PAGE_SHIFT))
			return (unsigned long) -EINVAL;

		offset = pgoff << PAGE_SHIFT;
		if (offset > mtd->size - len)
			return (unsigned long) -EINVAL;

		return mtd->get_unmapped_area(mtd, len, offset, flags);
	}

	/* can't map directly */
	return (unsigned long) -ENOSYS;
}