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
struct TYPE_2__ {int genMode; int dirtyState; } ;

/* Variables and functions */
 int _SHIFTL (int,int,int) ; 
 TYPE_1__* __gx ; 

void GX_SetCullMode(u8 mode)
{
    static u8 cm2hw[] = { 0, 2, 1, 3 };

	__gx->genMode = (__gx->genMode&~0xC000)|(_SHIFTL(cm2hw[mode],14,2));
	__gx->dirtyState |= 0x0004;
}