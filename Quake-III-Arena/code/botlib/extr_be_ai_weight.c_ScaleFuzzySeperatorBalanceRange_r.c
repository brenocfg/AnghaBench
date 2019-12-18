#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ type; double minweight; double maxweight; struct TYPE_3__* next; struct TYPE_3__* child; } ;
typedef  TYPE_1__ fuzzyseperator_t ;

/* Variables and functions */
 scalar_t__ WT_BALANCE ; 

void ScaleFuzzySeperatorBalanceRange_r(fuzzyseperator_t *fs, float scale)
{
	if (fs->child)
	{
		ScaleFuzzySeperatorBalanceRange_r(fs->child, scale);
	} //end if
	else if (fs->type == WT_BALANCE)
	{
		float mid = (fs->minweight + fs->maxweight) * 0.5;
		//get the weight between bounds
		fs->maxweight = mid + (fs->maxweight - mid) * scale;
		fs->minweight = mid + (fs->minweight - mid) * scale;
		if (fs->maxweight < fs->minweight)
		{
			fs->maxweight = fs->minweight;
		} //end if
	} //end else if
	if (fs->next) ScaleFuzzySeperatorBalanceRange_r(fs->next, scale);
}