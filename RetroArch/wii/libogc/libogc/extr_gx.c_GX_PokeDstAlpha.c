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

/* Variables and functions */
 int _SHIFTL (int,int,int) ; 
 int* _peReg ; 

void GX_PokeDstAlpha(u8 enable,u8 a)
{
	_peReg[2] = (_SHIFTL(enable,8,1))|(a&0xff);
}