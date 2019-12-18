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
struct _timing {int be3; int bs3; int be1; int bs1; int be4; int bs4; int be2; int bs2; } ;

/* Variables and functions */
 int /*<<< orphan*/  VI_REGCHANGE (int) ; 
 int /*<<< orphan*/  changed ; 
 int* regs ; 

__attribute__((used)) static inline void __setBBIntervalRegs(const struct _timing *tm)
{
	regs[10] = (tm->be3<<5)|tm->bs3;
	regs[11] = (tm->be1<<5)|tm->bs1;
	changed |= VI_REGCHANGE(10);
	changed |= VI_REGCHANGE(11);

	regs[12] = (tm->be4<<5)|tm->bs4;
	regs[13] = (tm->be2<<5)|tm->bs2;
	changed |= VI_REGCHANGE(12);
	changed |= VI_REGCHANGE(13);
}