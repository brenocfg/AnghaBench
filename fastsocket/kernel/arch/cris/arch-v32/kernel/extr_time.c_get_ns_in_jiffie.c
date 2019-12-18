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
typedef  int reg_timer_r_tmr0_data ;

/* Variables and functions */
 int REG_RD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TIMER0_DIV ; 
 int /*<<< orphan*/  r_tmr0_data ; 
 int /*<<< orphan*/  regi_timer0 ; 
 int /*<<< orphan*/  timer ; 

unsigned long get_ns_in_jiffie(void)
{
	reg_timer_r_tmr0_data data;
	unsigned long ns;

	data = REG_RD(timer, regi_timer0, r_tmr0_data);
	ns = (TIMER0_DIV - data) * 10;
	return ns;
}