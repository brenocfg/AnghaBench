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
struct mtd_info {struct map_info* priv; } ;
struct map_info {scalar_t__ virt; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long mapram_unmapped_area(struct mtd_info *mtd,
					  unsigned long len,
					  unsigned long offset,
					  unsigned long flags)
{
	struct map_info *map = mtd->priv;
	return (unsigned long) map->virt + offset;
}