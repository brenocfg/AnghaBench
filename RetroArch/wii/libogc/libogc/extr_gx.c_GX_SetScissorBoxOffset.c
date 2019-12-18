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
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 
 int _SHIFTL (int,int,int) ; 
 int _SHIFTR (int,int,int) ; 

void GX_SetScissorBoxOffset(s32 xoffset,s32 yoffset)
{
	s32 xoff = _SHIFTR((xoffset+0x156),1,24);
	s32 yoff = _SHIFTR((yoffset+0x156),1,24);

	GX_LOAD_BP_REG((0x59000000|(_SHIFTL(yoff,10,10))|(xoff&0x3ff)));
}