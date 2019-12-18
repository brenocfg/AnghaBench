#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int contents; } ;
struct TYPE_3__ {int* children; } ;

/* Variables and functions */
#define  Q1_CONTENTS_CLIP 142 
#define  Q1_CONTENTS_CURRENT_0 141 
#define  Q1_CONTENTS_CURRENT_180 140 
#define  Q1_CONTENTS_CURRENT_270 139 
#define  Q1_CONTENTS_CURRENT_90 138 
#define  Q1_CONTENTS_CURRENT_DOWN 137 
#define  Q1_CONTENTS_CURRENT_UP 136 
#define  Q1_CONTENTS_EMPTY 135 
#define  Q1_CONTENTS_LAVA 134 
#define  Q1_CONTENTS_ORIGIN 133 
#define  Q1_CONTENTS_SKY 132 
#define  Q1_CONTENTS_SLIME 131 
#define  Q1_CONTENTS_SOLID 130 
#define  Q1_CONTENTS_TRANSLUCENT 129 
#define  Q1_CONTENTS_WATER 128 
 TYPE_2__* q1_dleafs ; 
 TYPE_1__* q1_dnodes ; 

int Q1_SolidTree_r(int nodenum)
{
	if (nodenum < 0)
	{
		switch(q1_dleafs[(-nodenum) - 1].contents)
		{
			case Q1_CONTENTS_EMPTY:
			{
				return false;
			} //end case
			case Q1_CONTENTS_SOLID:
#ifdef HLCONTENTS
			case Q1_CONTENTS_CLIP:
#endif HLCONTENTS
			case Q1_CONTENTS_SKY:
#ifdef HLCONTENTS
			case Q1_CONTENTS_TRANSLUCENT:
#endif HLCONTENTS
			{
				return true;
			} //end case
			case Q1_CONTENTS_WATER:
			case Q1_CONTENTS_SLIME:
			case Q1_CONTENTS_LAVA:
#ifdef HLCONTENTS
			//these contents should not be found in the BSP
			case Q1_CONTENTS_ORIGIN:
			case Q1_CONTENTS_CURRENT_0:
			case Q1_CONTENTS_CURRENT_90:
			case Q1_CONTENTS_CURRENT_180:
			case Q1_CONTENTS_CURRENT_270:
			case Q1_CONTENTS_CURRENT_UP:
			case Q1_CONTENTS_CURRENT_DOWN:
#endif HLCONTENTS
			default:
			{
				return false;
			} //end default
		} //end switch
		return false;
	} //end if
	if (!Q1_SolidTree_r(q1_dnodes[nodenum].children[0])) return false;
	if (!Q1_SolidTree_r(q1_dnodes[nodenum].children[1])) return false;
	return true;
}