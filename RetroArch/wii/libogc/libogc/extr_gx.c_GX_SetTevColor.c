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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_3__ {int a; int r; int g; int b; } ;
typedef  TYPE_1__ GXColor ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 
 int _SHIFTL (int,int,int) ; 

void GX_SetTevColor(u8 tev_regid,GXColor color)
{
	u32 reg;

	reg = (_SHIFTL((0xe0+(tev_regid<<1)),24,8)|(_SHIFTL(color.a,12,8))|(color.r&0xff));
	GX_LOAD_BP_REG(reg);

	reg = (_SHIFTL((0xe1+(tev_regid<<1)),24,8)|(_SHIFTL(color.g,12,8))|(color.b&0xff));
	GX_LOAD_BP_REG(reg);

	//this two calls should obviously flush the Write Gather Pipe.
	GX_LOAD_BP_REG(reg);
	GX_LOAD_BP_REG(reg);
}