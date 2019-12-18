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
typedef  int /*<<< orphan*/  u32 ;
struct _timing {int /*<<< orphan*/  psbEven; int /*<<< orphan*/  psbOdd; int /*<<< orphan*/  prbEven; int /*<<< orphan*/  prbOdd; int /*<<< orphan*/  acv; int /*<<< orphan*/  equ; } ;
struct TYPE_2__ {int black; int /*<<< orphan*/  dispSizeY; int /*<<< orphan*/  adjustedDispPosY; struct _timing* timing; } ;

/* Variables and functions */
 TYPE_1__ HorVer ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __setVerticalRegs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void VIDEO_SetBlack(bool black)
{
	u32 level;
	const struct _timing *curtiming;

	_CPU_ISR_Disable(level);
	HorVer.black = black;
	curtiming = HorVer.timing;
	__setVerticalRegs(HorVer.adjustedDispPosY,HorVer.dispSizeY,curtiming->equ,curtiming->acv,curtiming->prbOdd,curtiming->prbEven,curtiming->psbOdd,curtiming->psbEven,HorVer.black);
	_CPU_ISR_Restore(level);
}