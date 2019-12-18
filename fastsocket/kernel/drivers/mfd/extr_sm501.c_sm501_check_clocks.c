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
struct sm501_devdata {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ SM501_CURRENT_CLOCK ; 
 unsigned long SM501_POWERMODE_M1_SRC ; 
 unsigned long SM501_POWERMODE_M_SRC ; 
 unsigned long readl (scalar_t__) ; 

__attribute__((used)) static int sm501_check_clocks(struct sm501_devdata *sm)
{
	unsigned long pwrmode = readl(sm->regs + SM501_CURRENT_CLOCK);
	unsigned long msrc = (pwrmode & SM501_POWERMODE_M_SRC);
	unsigned long m1src = (pwrmode & SM501_POWERMODE_M1_SRC);

	return ((msrc == 0 && m1src != 0) || (msrc != 0 && m1src == 0));
}