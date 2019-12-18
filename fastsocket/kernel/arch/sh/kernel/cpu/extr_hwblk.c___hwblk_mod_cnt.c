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
struct hwblk_info {struct hwblk* hwblks; } ;
struct hwblk {int* cnt; int /*<<< orphan*/  area; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwblk_area_mod_cnt (struct hwblk_info*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int __hwblk_mod_cnt(struct hwblk_info *info, int hwblk,
			  int counter, int value, int goal)
{
	struct hwblk *hp = info->hwblks + hwblk;

	hp->cnt[counter] += value;
	if (hp->cnt[counter] == goal)
		hwblk_area_mod_cnt(info, hp->area, counter, value, goal);

	return hp->cnt[counter];
}