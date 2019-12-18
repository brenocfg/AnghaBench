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
struct hwblk_info {struct hwblk_area* areas; } ;
struct hwblk_area {int* cnt; int flags; int parent; } ;

/* Variables and functions */
 int HWBLK_AREA_FLAG_PARENT ; 

__attribute__((used)) static void hwblk_area_mod_cnt(struct hwblk_info *info,
			       int area, int counter, int value, int goal)
{
	struct hwblk_area *hap = info->areas + area;

	hap->cnt[counter] += value;

	if (hap->cnt[counter] != goal)
		return;

	if (hap->flags & HWBLK_AREA_FLAG_PARENT)
		hwblk_area_mod_cnt(info, hap->parent, counter, value, goal);
}