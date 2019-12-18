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
struct mtd_info {int numeraseregions; TYPE_1__* eraseregions; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {scalar_t__ offset; } ;

/* Variables and functions */

int flexonenand_region(struct mtd_info *mtd, loff_t addr)
{
	int i;

	for (i = 0; i < mtd->numeraseregions; i++)
		if (addr < mtd->eraseregions[i].offset)
			break;
	return i - 1;
}