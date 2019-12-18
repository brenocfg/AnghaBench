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

/* Variables and functions */
 int SIS_315_VGA ; 
 unsigned short SiS_GetModeID (int,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int VB2_30xB ; 
 unsigned int VB2_SISVGA2BRIDGE ; 

unsigned short
SiS_GetModeID_VGA2(int VGAEngine, unsigned int VBFlags, int HDisplay, int VDisplay, int Depth,
			unsigned int VBFlags2)
{
   if(!(VBFlags2 & VB2_SISVGA2BRIDGE)) return 0;

   if(HDisplay >= 1920) return 0;

   switch(HDisplay)
   {
	case 1600:
		if(VDisplay == 1200) {
			if(VGAEngine != SIS_315_VGA) return 0;
			if(!(VBFlags2 & VB2_30xB)) return 0;
		}
		break;
	case 1680:
		if(VDisplay == 1050) {
			if(VGAEngine != SIS_315_VGA) return 0;
			if(!(VBFlags2 & VB2_30xB)) return 0;
		}
		break;
   }

   return SiS_GetModeID(VGAEngine, 0, HDisplay, VDisplay, Depth, false, 0, 0);
}