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
typedef  int u16 ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  VI_REGCHANGE (int) ; 
 int /*<<< orphan*/  changed ; 
 int* regs ; 

__attribute__((used)) static inline void __setVerticalRegs(u16 dispPosY,u16 dispSizeY,u8 equ,u16 acv,u16 prbOdd,u16 prbEven,u16 psbOdd,u16 psbEven,s32 black)
{
	u16 tmp;
	u32 div1,div2;
	u32 psb,prb;
	u32 psbodd,prbodd;
	u32 psbeven,prbeven;

	div1 = 2;
	div2 = 1;
	if(equ>=10) {
		div1 = 1;
		div2 = 2;
	}

	prb = div2*dispPosY;
	psb = div2*(((acv*div1)-dispSizeY)-dispPosY);
	if(dispPosY%2) {
		prbodd = prbEven+prb;
		psbodd = psbEven+psb;
		prbeven = prbOdd+prb;
		psbeven = psbOdd+psb;
	} else {
		prbodd = prbOdd+prb;
		psbodd = psbOdd+psb;
		prbeven = prbEven+prb;
		psbeven = psbEven+psb;
	}

	tmp = dispSizeY/div1;
	if(black) {
		prbodd += ((tmp<<1)-2);
		prbeven += ((tmp<<1)-2);
		psbodd += 2;
		psbeven += 2;
		tmp = 0;
	}

	regs[0] = ((tmp<<4)&~0x0f)|equ;
	changed |= VI_REGCHANGE(0);

	regs[6] = psbodd;
	regs[7] = prbodd;
	changed |= VI_REGCHANGE(6);
	changed |= VI_REGCHANGE(7);

	regs[8] = psbeven;
	regs[9] = prbeven;
	changed |= VI_REGCHANGE(8);
	changed |= VI_REGCHANGE(9);
}