#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int s32 ;
struct TYPE_5__ {int* chnMatColor; int dirtyState; } ;
struct TYPE_4__ {int a; int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ GXColor ;

/* Variables and functions */
#define  GX_ALPHA0 133 
#define  GX_ALPHA1 132 
#define  GX_COLOR0 131 
#define  GX_COLOR0A0 130 
#define  GX_COLOR1 129 
#define  GX_COLOR1A1 128 
 int _SHIFTL (int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* __gx ; 

void GX_SetChanMatColor(s32 channel,GXColor color)
{
	u32 reg,val = (_SHIFTL(color.r,24,8))|(_SHIFTL(color.g,16,8))|(_SHIFTL(color.b,8,8))|0x00;
	switch(channel) {
		case GX_COLOR0:
			reg = 0;
			val |= (__gx->chnMatColor[0]&0xff);
			break;
		case GX_COLOR1:
			reg = 1;
			val |= (__gx->chnMatColor[1]&0xff);
			break;
		case GX_ALPHA0:
			reg = 0;
			val = ((__gx->chnMatColor[0]&~0xff)|(color.a&0xff));
			break;
		case GX_ALPHA1:
			reg = 1;
			val = ((__gx->chnMatColor[1]&~0xff)|(color.a&0xff));
			break;
		case GX_COLOR0A0:
			reg = 0;
			val |= (color.a&0xFF);
			break;
		case GX_COLOR1A1:
			reg = 1;
			val |= (color.a&0xFF);
			break;
		default:
			return;
	}

	__gx->chnMatColor[reg] = val;
	__gx->dirtyState |= (0x0400<<reg);
}