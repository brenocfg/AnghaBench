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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int U8; int U32; } ;

/* Variables and functions */
#define  GX_LIGHT0 135 
#define  GX_LIGHT1 134 
#define  GX_LIGHT2 133 
#define  GX_LIGHT3 132 
#define  GX_LIGHT4 131 
#define  GX_LIGHT5 130 
#define  GX_LIGHT6 129 
#define  GX_LIGHT7 128 
 int _SHIFTL (int,int,int) ; 
 TYPE_1__* wgPipe ; 

void GX_LoadLightObjIdx(u32 litobjidx,u8 litid)
{
	u32 reg;
	u32 idx = 0;

	switch(litid) {
		case GX_LIGHT0:
			idx = 0;
			break;
		case GX_LIGHT1:
			idx = 1;
			break;
		case GX_LIGHT2:
			idx = 2;
			break;
		case GX_LIGHT3:
			idx = 3;
			break;
		case GX_LIGHT4:
			idx = 4;
			break;
		case GX_LIGHT5:
			idx = 5;
			break;
		case GX_LIGHT6:
			idx = 6;
			break;
		case GX_LIGHT7:
			idx = 7;
			break;
		default:
			idx = 0;
			break;

	}

	reg = 0xf600|(_SHIFTL(idx,4,8));
	reg = (reg&~0xffff0000)|(_SHIFTL(litobjidx,16,16));

	wgPipe->U8 = 0x38;
	wgPipe->U32 = reg;
}