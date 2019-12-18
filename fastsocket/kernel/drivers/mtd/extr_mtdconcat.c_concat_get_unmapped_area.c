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
struct mtd_info {unsigned long size; unsigned long (* get_unmapped_area ) (struct mtd_info*,unsigned long,unsigned long,unsigned long) ;} ;
struct mtd_concat {int num_subdev; struct mtd_info** subdev; } ;

/* Variables and functions */
 struct mtd_concat* CONCAT (struct mtd_info*) ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOSYS ; 
 unsigned long stub1 (struct mtd_info*,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long concat_get_unmapped_area(struct mtd_info *mtd,
					      unsigned long len,
					      unsigned long offset,
					      unsigned long flags)
{
	struct mtd_concat *concat = CONCAT(mtd);
	int i;

	for (i = 0; i < concat->num_subdev; i++) {
		struct mtd_info *subdev = concat->subdev[i];

		if (offset >= subdev->size) {
			offset -= subdev->size;
			continue;
		}

		/* we've found the subdev over which the mapping will reside */
		if (offset + len > subdev->size)
			return (unsigned long) -EINVAL;

		if (subdev->get_unmapped_area)
			return subdev->get_unmapped_area(subdev, len, offset,
							 flags);

		break;
	}

	return (unsigned long) -ENOSYS;
}