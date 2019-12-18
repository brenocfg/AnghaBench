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
typedef  size_t u32 ;
struct TYPE_2__ {int* tevAlphaEnv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 
 int _SHIFTL (int,int,int) ; 
 TYPE_1__* __gx ; 

void GX_SetTevSwapMode(u8 tevstage,u8 ras_sel,u8 tex_sel)
{
	u32 reg = (tevstage&0xf);
	__gx->tevAlphaEnv[reg] = (__gx->tevAlphaEnv[reg]&~0x3)|(ras_sel&0x3);
	__gx->tevAlphaEnv[reg] = (__gx->tevAlphaEnv[reg]&~0xC)|(_SHIFTL(tex_sel,2,2));
	GX_LOAD_BP_REG(__gx->tevAlphaEnv[reg]);
}