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
struct TYPE_2__ {int* tevRasOrder; } ;

/* Variables and functions */
#define  GX_INDTEXSTAGE0 131 
#define  GX_INDTEXSTAGE1 130 
#define  GX_INDTEXSTAGE2 129 
#define  GX_INDTEXSTAGE3 128 
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 
 int _SHIFTL (int,int,int) ; 
 TYPE_1__* __gx ; 

void GX_SetIndTexCoordScale(u8 indtexid,u8 scale_s,u8 scale_t)
{
	switch(indtexid) {
		case GX_INDTEXSTAGE0:
			__gx->tevRasOrder[0] = (__gx->tevRasOrder[0]&~0x0f)|(scale_s&0x0f);
			__gx->tevRasOrder[0] = (__gx->tevRasOrder[0]&~0xF0)|(_SHIFTL(scale_t,4,4));
			GX_LOAD_BP_REG(__gx->tevRasOrder[0]);
			break;
		case GX_INDTEXSTAGE1:
			__gx->tevRasOrder[0] = (__gx->tevRasOrder[0]&~0xF00)|(_SHIFTL(scale_s,8,4));
			__gx->tevRasOrder[0] = (__gx->tevRasOrder[0]&~0xF000)|(_SHIFTL(scale_t,12,4));
			GX_LOAD_BP_REG(__gx->tevRasOrder[0]);
			break;
		case GX_INDTEXSTAGE2:
			__gx->tevRasOrder[1] = (__gx->tevRasOrder[1]&~0x0f)|(scale_s&0x0f);
			__gx->tevRasOrder[1] = (__gx->tevRasOrder[1]&~0xF0)|(_SHIFTL(scale_t,4,4));
			GX_LOAD_BP_REG(__gx->tevRasOrder[1]);
			break;
		case GX_INDTEXSTAGE3:
			__gx->tevRasOrder[1] = (__gx->tevRasOrder[1]&~0xF00)|(_SHIFTL(scale_s,8,4));
			__gx->tevRasOrder[1] = (__gx->tevRasOrder[1]&~0xF000)|(_SHIFTL(scale_t,12,4));
			GX_LOAD_BP_REG(__gx->tevRasOrder[1]);
			break;
	}
}