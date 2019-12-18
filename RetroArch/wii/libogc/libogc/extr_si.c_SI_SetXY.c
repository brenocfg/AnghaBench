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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int poll; } ;

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int _SHIFTL (int /*<<< orphan*/ ,int,int) ; 
 int* _siReg ; 
 TYPE_1__ sicntrl ; 

void SI_SetXY(u16 line,u8 cnt)
{
	u32 level;
	_CPU_ISR_Disable(level);
	sicntrl.poll = (sicntrl.poll&~0x3ffff00)|_SHIFTL(line,16,10)|_SHIFTL(cnt,8,8);
	_siReg[12] = sicntrl.poll;
	_CPU_ISR_Restore(level);
}