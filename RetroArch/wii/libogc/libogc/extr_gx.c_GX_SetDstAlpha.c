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
struct TYPE_2__ {int peCMode1; } ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 
 int _SHIFTL (int,int,int) ; 
 TYPE_1__* __gx ; 

void GX_SetDstAlpha(u8 enable,u8 a)
{
	__gx->peCMode1 = (__gx->peCMode1&~0xff)|(a&0xff);
	__gx->peCMode1 = (__gx->peCMode1&~0x100)|(_SHIFTL(enable,8,1));
	GX_LOAD_BP_REG(__gx->peCMode1);
}