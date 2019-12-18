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
typedef  int u16 ;
struct _timing {int nhlines; int hlw; } ;

/* Variables and functions */
 int /*<<< orphan*/  VI_REGCHANGE (int) ; 
 int /*<<< orphan*/  changed ; 
 int* regs ; 

__attribute__((used)) static inline void __setInterruptRegs(const struct _timing *tm)
{
	u16 hlw;

	hlw = 0;
	if(tm->nhlines%2) hlw = tm->hlw;
	regs[24] = 0x1000|((tm->nhlines/2)+1);
	regs[25] = hlw+1;
	changed |= VI_REGCHANGE(24);
	changed |= VI_REGCHANGE(25);
}