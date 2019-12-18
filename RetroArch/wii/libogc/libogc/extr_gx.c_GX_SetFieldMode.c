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
struct TYPE_2__ {int lpWidth; } ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 
 int _SHIFTL (int,int,int) ; 
 int /*<<< orphan*/  __GX_FlushTextureState () ; 
 TYPE_1__* __gx ; 

void GX_SetFieldMode(u8 field_mode,u8 half_aspect_ratio)
{
	__gx->lpWidth = (__gx->lpWidth&~0x400000)|(_SHIFTL(half_aspect_ratio,22,1));
	GX_LOAD_BP_REG(__gx->lpWidth);

	__GX_FlushTextureState();
	GX_LOAD_BP_REG(0x68000000|(field_mode&1));
	__GX_FlushTextureState();
}