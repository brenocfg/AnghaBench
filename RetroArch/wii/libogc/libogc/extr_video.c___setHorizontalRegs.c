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
typedef  int u32 ;
typedef  int u16 ;
struct _timing {int hcs; int hce; int hlw; int hbe640; int hbs640; int hsy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VI_REGCHANGE (int) ; 
 int /*<<< orphan*/  changed ; 
 int* regs ; 

__attribute__((used)) static inline void __setHorizontalRegs(const struct _timing *tm,u16 dispPosX,u16 dispSizeX)
{
	u32 val1,val2;

	regs[2] = (tm->hcs<<8)|tm->hce;
	regs[3] = tm->hlw;
	changed |= VI_REGCHANGE(2);
	changed |= VI_REGCHANGE(3);

	val1 = (tm->hbe640+dispPosX-40)&0x01ff;
	val2 = (tm->hbs640+dispPosX+40)-(720-dispSizeX);
	regs[4] = (val1>>9)|(val2<<1);
	regs[5] = (val1<<7)|tm->hsy;
	changed |= VI_REGCHANGE(4);
	changed |= VI_REGCHANGE(5);
}