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
struct mtd_part {TYPE_1__* master; scalar_t__ offset; } ;
struct mtd_info {int dummy; } ;
struct TYPE_2__ {unsigned long (* get_unmapped_area ) (TYPE_1__*,unsigned long,unsigned long,unsigned long) ;} ;

/* Variables and functions */
 struct mtd_part* PART (struct mtd_info*) ; 
 unsigned long stub1 (TYPE_1__*,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long part_get_unmapped_area(struct mtd_info *mtd,
					    unsigned long len,
					    unsigned long offset,
					    unsigned long flags)
{
	struct mtd_part *part = PART(mtd);

	offset += part->offset;
	return part->master->get_unmapped_area(part->master, len, offset,
					       flags);
}