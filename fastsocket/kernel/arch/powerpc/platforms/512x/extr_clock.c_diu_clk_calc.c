#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct clk {unsigned long rate; } ;
struct TYPE_4__ {int scfr1; } ;
struct TYPE_3__ {unsigned long rate; } ;

/* Variables and functions */
 TYPE_2__* clockctl ; 
 TYPE_1__ sys_clk ; 

__attribute__((used)) static void diu_clk_calc(struct clk *clk)
{
	int diudiv_x_2 = clockctl->scfr1 & 0xff;
	unsigned long rate;

	rate = sys_clk.rate;

	rate *= 2;
	rate /= diudiv_x_2;

	clk->rate = rate;
}