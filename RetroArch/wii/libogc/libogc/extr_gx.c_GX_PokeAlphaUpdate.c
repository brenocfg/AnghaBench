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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int _SHIFTL (int /*<<< orphan*/ ,int,int) ; 
 int* _peReg ; 

void GX_PokeAlphaUpdate(u8 update_enable)
{
	_peReg[1] = (_peReg[1]&~0x10)|(_SHIFTL(update_enable,4,1));
}