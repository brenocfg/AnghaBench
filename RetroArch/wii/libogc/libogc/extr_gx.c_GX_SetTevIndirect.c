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

void GX_SetTevIndirect(u8 tevstage,u8 indtexid,u8 format,u8 bias,u8 mtxid,u8 wrap_s,u8 wrap_t,u8 addprev,u8 utclod,u8 a)
{
	u32 val = (0x10000000|(_SHIFTL(tevstage,24,4)))|(indtexid&3)|(_SHIFTL(format,2,2))|(_SHIFTL(bias,4,3))|(_SHIFTL(a,7,2))|(_SHIFTL(mtxid,9,4))|(_SHIFTL(wrap_s,13,3))|(_SHIFTL(wrap_t,16,3))|(_SHIFTL(utclod,19,1))|(_SHIFTL(addprev,20,1));
	GX_LOAD_BP_REG(val);
}