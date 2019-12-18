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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 
 int _SHIFTL (int,int,int) ; 

void GX_SetAlphaCompare(u8 comp0,u8 ref0,u8 aop,u8 comp1,u8 ref1)
{
	u32 val = 0;
	val = (_SHIFTL(aop,22,2))|(_SHIFTL(comp1,19,3))|(_SHIFTL(comp0,16,3))|(_SHIFTL(ref1,8,8))|(ref0&0xff);
	GX_LOAD_BP_REG(0xf3000000|val);
}