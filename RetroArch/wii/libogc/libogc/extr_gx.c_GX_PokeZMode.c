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
typedef  int u16 ;

/* Variables and functions */
 int _SHIFTL (int,int,int) ; 
 int* _peReg ; 

void GX_PokeZMode(u8 comp_enable,u8 func,u8 update_enable)
{
	u16 regval;
	regval = comp_enable&0x1;
	regval = (regval&~0xE)|(_SHIFTL(func,1,3));
	regval = (regval&0x10)|(_SHIFTL(update_enable,4,1));
	_peReg[0] = regval;
}