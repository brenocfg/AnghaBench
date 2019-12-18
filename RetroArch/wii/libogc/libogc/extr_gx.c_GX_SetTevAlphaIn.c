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

void GX_SetTevAlphaIn(u8 tevstage,u8 a,u8 b,u8 c,u8 d)
{
	u32 reg = (tevstage&0xf);
	__gx->tevAlphaEnv[reg] = (__gx->tevAlphaEnv[reg]&~0xE000)|(_SHIFTL(a,13,3));
	__gx->tevAlphaEnv[reg] = (__gx->tevAlphaEnv[reg]&~0x1C00)|(_SHIFTL(b,10,3));
	__gx->tevAlphaEnv[reg] = (__gx->tevAlphaEnv[reg]&~0x380)|(_SHIFTL(c,7,3));
	__gx->tevAlphaEnv[reg] = (__gx->tevAlphaEnv[reg]&~0x70)|(_SHIFTL(d,4,3));

	GX_LOAD_BP_REG(__gx->tevAlphaEnv[reg]);
}